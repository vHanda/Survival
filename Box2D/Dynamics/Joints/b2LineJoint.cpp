/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Dynamics/Joints/b2LineJoint.h"
#include "Dynamics/b2Body.h"
#include "Dynamics/b2World.h"

// Linear constraint (point-to-line)
// d = p2 - p1 = x2 + r2 - x1 - r1
// C = dot(perp, d)
// Cdot = dot(d, cross(w1, perp)) + dot(perp, v2 + cross(w2, r2) - v1 - cross(w1, r1))
//      = -dot(perp, v1) - dot(cross(d + r1, perp), w1) + dot(perp, v2) + dot(cross(r2, perp), v2)
// J = [-perp, -cross(d + r1, perp), perp, cross(r2,perp)]
//
// K = J * invM * JT
//
// J = [-a -s1 a s2]
// a = perp
// s1 = cross(d + r1, a) = cross(p2 - x1, a)
// s2 = cross(r2, a) = cross(p2 - x2, a)


// Motor/Limit linear constraint
// C = dot(ax1, d)
// Cdot = = -dot(ax1, v1) - dot(cross(d + r1, ax1), w1) + dot(ax1, v2) + dot(cross(r2, ax1), v2)
// J = [-ax1 -cross(d+r1,ax1) ax1 cross(r2,ax1)]

// Block Solver
// We develop a block solver that includes the joint limit. This makes the limit stiff (inelastic) even
// when the mass has poor distribution (leading to large torques about the joint anchor points).
//
// The Jacobian has 3 rows:
// J = [-uT -s1 uT s2] // linear
//     [-vT -a1 vT a2] // limit
//
// u = perp
// v = axis
// s1 = cross(d + r1, u), s2 = cross(r2, u)
// a1 = cross(d + r1, v), a2 = cross(r2, v)

// M * (v2 - v1) = JT * df
// J * v2 = bias
//
// v2 = v1 + invM * JT * df
// J * (v1 + invM * JT * df) = bias
// K * df = bias - J * v1 = -Cdot
// K = J * invM * JT
// Cdot = J * v1 - bias
//
// Now solve for f2.
// df = f2 - f1
// K * (f2 - f1) = -Cdot
// f2 = invK * (-Cdot) + f1
//
// Clamp accumulated limit impulse.
// lower: f2(2) = max(f2(2), 0)
// upper: f2(2) = min(f2(2), 0)
//
// Solve for correct f2(1)
// K(1,1) * f2(1) = -Cdot(1) - K(1,2) * f2(2) + K(1,1:2) * f1
//                = -Cdot(1) - K(1,2) * f2(2) + K(1,1) * f1(1) + K(1,2) * f1(2)
// K(1,1) * f2(1) = -Cdot(1) - K(1,2) * (f2(2) - f1(2)) + K(1,1) * f1(1)
// f2(1) = invK(1,1) * (-Cdot(1) - K(1,2) * (f2(2) - f1(2))) + f1(1)
//
// Now compute impulse to be applied:
// df = f2 - f1

void b2LineJointDef::Initialize(b2Body* b1, b2Body* b2, const b2Vec2& anchor, const b2Vec2& axis)
{
	body1 = b1;
	body2 = b2;
	localAnchor1 = body1->GetLocalPoint(anchor);
	localAnchor2 = body2->GetLocalPoint(anchor);
	localAxis1 = body1->GetLocalVector(axis);
}

b2LineJoint::b2LineJoint(const b2LineJointDef* def)
: b2Joint(def)
{
	m_localAnchor1 = def->localAnchor1;
	m_localAnchor2 = def->localAnchor2;
	m_localXAxis1 = def->localAxis1;
	m_localYAxis1 = b2Cross(1.0f, m_localXAxis1);

	m_impulse.SetZero();
	m_motorMass = 0.0;
	m_motorImpulse = 0.0f;

	m_lowerTranslation = def->lowerTranslation;
	m_upperTranslation = def->upperTranslation;
	m_maxMotorForce = B2FORCE_INV_SCALE(def->maxMotorForce);
	m_motorSpeed = def->motorSpeed;
	m_enableLimit = def->enableLimit;
	m_enableMotor = def->enableMotor;
	m_limitState = e_inactiveLimit;

	m_axis.SetZero();
	m_perp.SetZero();
}

void b2LineJoint::InitVelocityConstraints(const b2TimeStep& step)
{
	b2Body* b1 = m_body1;
	b2Body* b2 = m_body2;

	m_localCenter1 = b1->GetLocalCenter();
	m_localCenter2 = b2->GetLocalCenter();

	b2XForm xf1 = b1->GetXForm();
	b2XForm xf2 = b2->GetXForm();

	// Compute the effective masses.
	b2Vec2 r1 = b2Mul(xf1.R, m_localAnchor1 - m_localCenter1);
	b2Vec2 r2 = b2Mul(xf2.R, m_localAnchor2 - m_localCenter2);
	b2Vec2 d = b2->m_sweep.c + r2 - b1->m_sweep.c - r1;

	m_invMass1 = b1->m_invMass;
	m_invI1 = b1->m_invI;
	m_invMass2 = b2->m_invMass;
	m_invI2 = b2->m_invI;

	// Compute motor Jacobian and effective mass.
	{
		m_axis = b2Mul(xf1.R, m_localXAxis1);
		m_a1 = b2Cross(d + r1, m_axis);
		m_a2 = b2Cross(r2, m_axis);

		m_motorMass = m_invMass1 + m_invMass2 + m_invI1 * m_a1 * m_a1 + m_invI2 * m_a2 * m_a2;
		b2Assert(m_motorMass > B2_FLT_EPSILON);
		m_motorMass = 1.0f / m_motorMass;
	}

	// Prismatic constraint.
	{
		m_perp = b2Mul(xf1.R, m_localYAxis1);

		m_s1 = b2Cross(d + r1, m_perp);
		m_s2 = b2Cross(r2, m_perp);

		float32 m1 = m_invMass1, m2 = m_invMass2;
		float32 i1 = m_invI1, i2 = m_invI2;

		float32 k11 = m1 + m2 + i1 * m_s1 * m_s1 + i2 * m_s2 * m_s2;
		float32 k12 = i1 * m_s1 * m_a1 + i2 * m_s2 * m_a2;
		float32 k22 = m1 + m2 + i1 * m_a1 * m_a1 + i2 * m_a2 * m_a2;

		m_K.col1.Set(k11, k12);
		m_K.col2.Set(k12, k22);
	}

	// Compute motor and limit terms.
	if (m_enableLimit)
	{
		float32 jointTranslation = b2Dot(m_axis, d);
		if (b2Abs(m_upperTranslation - m_lowerTranslation) < 2.0f * b2_linearSlop)
		{
			m_limitState = e_equalLimits;
		}
		else if (jointTranslation <= m_lowerTranslation)
		{
			if (m_limitState != e_atLowerLimit)
			{
				m_limitState = e_atLowerLimit;
				m_impulse.y = 0.0f;
			}
		}
		else if (jointTranslation >= m_upperTranslation)
		{
			if (m_limitState != e_atUpperLimit)
			{
				m_limitState = e_atUpperLimit;
				m_impulse.y = 0.0f;
			}
		}
		else
		{
			m_limitState = e_inactiveLimit;
			m_impulse.y = 0.0f;
		}
	}
	else
	{
		m_limitState = e_inactiveLimit;
	}

	if (m_enableMotor == false)
	{
		m_motorImpulse = 0.0f;
	}

	if (step.warmStarting)
	{
		// Account for variable time step.
		m_impulse *= step.dtRatio;
		m_motorImpulse *= step.dtRatio;

		b2Vec2 P = m_impulse.x * m_perp + (m_motorImpulse + m_impulse.y) * m_axis;
		float32 L1 = m_impulse.x * m_s1 + (m_motorImpulse + m_impulse.y) * m_a1;
		float32 L2 = m_impulse.x * m_s2 + (m_motorImpulse + m_impulse.y) * m_a2;

		b1->m_linearVelocity -= m_invMass1 * P;
		b1->m_angularVelocity -= m_invI1 * L1;

		b2->m_linearVelocity += m_invMass2 * P;
		b2->m_angularVelocity += m_invI2 * L2;
	}
	else
	{
		m_impulse.SetZero();
		m_motorImpulse = 0.0f;
	}
}

void b2LineJoint::SolveVelocityConstraints(const b2TimeStep& step)
{
	b2Body* b1 = m_body1;
	b2Body* b2 = m_body2;

	b2Vec2 v1 = b1->m_linearVelocity;
	float32 w1 = b1->m_angularVelocity;
	b2Vec2 v2 = b2->m_linearVelocity;
	float32 w2 = b2->m_angularVelocity;

	// Solve linear motor constraint.
	if (m_enableMotor && m_limitState != e_equalLimits)
	{
		float32 Cdot = b2Dot(m_axis, v2 - v1) + m_a2 * w2 - m_a1 * w1;
		float32 impulse = m_motorMass * (m_motorSpeed - Cdot);
		float32 oldImpulse = m_motorImpulse;
		float32 maxImpulse = step.dt * m_maxMotorForce;
		m_motorImpulse = b2Clamp(m_motorImpulse + impulse, -maxImpulse, maxImpulse);
		impulse = m_motorImpulse - oldImpulse;

		b2Vec2 P = impulse * m_axis;
		float32 L1 = impulse * m_a1;
		float32 L2 = impulse * m_a2;

		v1 -= m_invMass1 * P;
		w1 -= m_invI1 * L1;

		v2 += m_invMass2 * P;
		w2 += m_invI2 * L2;
	}

	float32 Cdot1 = b2Dot(m_perp, v2 - v1) + m_s2 * w2 - m_s1 * w1;

	if (m_enableLimit && m_limitState != e_inactiveLimit)
	{
		// Solve prismatic and limit constraint in block form.
		float32 Cdot2 = b2Dot(m_axis, v2 - v1) + m_a2 * w2 - m_a1 * w1;
		b2Vec2 Cdot(Cdot1, Cdot2);

		b2Vec2 f1 = m_impulse;
		b2Vec2 df =  m_K.Solve(-Cdot);
		m_impulse += df;

		if (m_limitState == e_atLowerLimit)
		{
			m_impulse.y = b2Max(m_impulse.y, 0.0f);
		}
		else if (m_limitState == e_atUpperLimit)
		{
			m_impulse.y = b2Min(m_impulse.y, 0.0f);
		}

		// f2(1) = invK(1,1) * (-Cdot(1) - K(1,2) * (f2(2) - f1(2))) + f1(1)
		float32 b = -Cdot1 - (m_impulse.y - f1.y) * m_K.col2.x;
		float32 f2r = b / m_K.col1.x + f1.x;
		m_impulse.x = f2r;

		df = m_impulse - f1;

		b2Vec2 P = df.x * m_perp + df.y * m_axis;
		float32 L1 = df.x * m_s1 + df.y * m_a1;
		float32 L2 = df.x * m_s2 + df.y * m_a2;

		v1 -= m_invMass1 * P;
		w1 -= m_invI1 * L1;

		v2 += m_invMass2 * P;
		w2 += m_invI2 * L2;
	}
	else
	{
		// Limit is inactive, just solve the prismatic constraint in block form.
		float32 df = (-Cdot1) / m_K.col1.x;
		m_impulse.x += df;

		b2Vec2 P = df * m_perp;
		float32 L1 = df * m_s1;
		float32 L2 = df * m_s2;

		v1 -= m_invMass1 * P;
		w1 -= m_invI1 * L1;

		v2 += m_invMass2 * P;
		w2 += m_invI2 * L2;
	}

	b1->m_linearVelocity = v1;
	b1->m_angularVelocity = w1;
	b2->m_linearVelocity = v2;
	b2->m_angularVelocity = w2;
}

bool b2LineJoint::SolvePositionConstraints(float32 baumgarte)
{
	B2_NOT_USED(baumgarte);

	b2Body* b1 = m_body1;
	b2Body* b2 = m_body2;

	b2Vec2 c1 = b1->m_sweep.c;
	float32 a1 = b1->m_sweep.a;

	b2Vec2 c2 = b2->m_sweep.c;
	float32 a2 = b2->m_sweep.a;

	// Solve linear limit constraint.
	float32 linearError = 0.0f, angularError = 0.0f;
	bool active = false;
	float32 C2 = 0.0f;

	b2Mat22 R1(a1), R2(a2);

	b2Vec2 r1 = b2Mul(R1, m_localAnchor1 - m_localCenter1);
	b2Vec2 r2 = b2Mul(R2, m_localAnchor2 - m_localCenter2);
	b2Vec2 d = c2 + r2 - c1 - r1;

	if (m_enableLimit)
	{
		m_axis = b2Mul(R1, m_localXAxis1);

		m_a1 = b2Cross(d + r1, m_axis);
		m_a2 = b2Cross(r2, m_axis);

		float32 translation = b2Dot(m_axis, d);
		if (b2Abs(m_upperTranslation - m_lowerTranslation) < 2.0f * b2_linearSlop)
		{
			// Prevent large angular corrections
			C2 = b2Clamp(translation, -b2_maxLinearCorrection, b2_maxLinearCorrection);
			linearError = b2Abs(translation);
			active = true;
		}
		else if (translation <= m_lowerTranslation)
		{
			// Prevent large linear corrections and allow some slop.
			C2 = b2Clamp(translation - m_lowerTranslation + b2_linearSlop, -b2_maxLinearCorrection, 0.0f);
			linearError = m_lowerTranslation - translation;
			active = true;
		}
		else if (translation >= m_upperTranslation)
		{
			// Prevent large linear corrections and allow some slop.
			C2 = b2Clamp(translation - m_upperTranslation - b2_linearSlop, 0.0f, b2_maxLinearCorrection);
			linearError = translation - m_upperTranslation;
			active = true;
		}
	}

	m_perp = b2Mul(R1, m_localYAxis1);

	m_s1 = b2Cross(d + r1, m_perp);
	m_s2 = b2Cross(r2, m_perp);

	b2Vec2 impulse;
	float32 C1;
	C1 = b2Dot(m_perp, d);

	linearError = b2Max(linearError, b2Abs(C1));
	angularError = 0.0f;

	if (active)
	{
		float32 m1 = m_invMass1, m2 = m_invMass2;
		float32 i1 = m_invI1, i2 = m_invI2;

		float32 k11 = m1 + m2 + i1 * m_s1 * m_s1 + i2 * m_s2 * m_s2;
		float32 k12 = i1 * m_s1 * m_a1 + i2 * m_s2 * m_a2;
		float32 k22 = m1 + m2 + i1 * m_a1 * m_a1 + i2 * m_a2 * m_a2;

		m_K.col1.Set(k11, k12);
		m_K.col2.Set(k12, k22);

		b2Vec2 C;
		C.x = C1;
		C.y = C2;

		impulse = m_K.Solve(-C);
	}
	else
	{
		float32 m1 = m_invMass1, m2 = m_invMass2;
		float32 i1 = m_invI1, i2 = m_invI2;

		float32 k11 = m1 + m2 + i1 * m_s1 * m_s1 + i2 * m_s2 * m_s2;

		float32 impulse1 = (-C1) / k11;
		impulse.x = impulse1;
		impulse.y = 0.0f;
	}

	b2Vec2 P = impulse.x * m_perp + impulse.y * m_axis;
	float32 L1 = impulse.x * m_s1 + impulse.y * m_a1;
	float32 L2 = impulse.x * m_s2 + impulse.y * m_a2;

	c1 -= m_invMass1 * P;
	a1 -= m_invI1 * L1;
	c2 += m_invMass2 * P;
	a2 += m_invI2 * L2;

	// TODO_ERIN remove need for this.
	b1->m_sweep.c = c1;
	b1->m_sweep.a = a1;
	b2->m_sweep.c = c2;
	b2->m_sweep.a = a2;
	b1->SynchronizeTransform();
	b2->SynchronizeTransform();

	return linearError <= b2_linearSlop && angularError <= b2_angularSlop;
}

b2Vec2 b2LineJoint::GetAnchor1() const
{
	return m_body1->GetWorldPoint(m_localAnchor1);
}

b2Vec2 b2LineJoint::GetAnchor2() const
{
	return m_body2->GetWorldPoint(m_localAnchor2);
}

b2Vec2 b2LineJoint::GetReactionForce(float32 inv_dt) const
{
	return inv_dt * (m_impulse.x * m_perp + (m_motorImpulse + m_impulse.y) * m_axis);
}

float32 b2LineJoint::GetReactionTorque(float32 inv_dt) const
{
	B2_NOT_USED(inv_dt);
	return 0.0f;
}

float32 b2LineJoint::GetJointTranslation() const
{
	b2Body* b1 = m_body1;
	b2Body* b2 = m_body2;

	b2Vec2 p1 = b1->GetWorldPoint(m_localAnchor1);
	b2Vec2 p2 = b2->GetWorldPoint(m_localAnchor2);
	b2Vec2 d = p2 - p1;
	b2Vec2 axis = b1->GetWorldVector(m_localXAxis1);

	float32 translation = b2Dot(d, axis);
	return translation;
}

float32 b2LineJoint::GetJointSpeed() const
{
	b2Body* b1 = m_body1;
	b2Body* b2 = m_body2;

	b2Vec2 r1 = b2Mul(b1->GetXForm().R, m_localAnchor1 - b1->GetLocalCenter());
	b2Vec2 r2 = b2Mul(b2->GetXForm().R, m_localAnchor2 - b2->GetLocalCenter());
	b2Vec2 p1 = b1->m_sweep.c + r1;
	b2Vec2 p2 = b2->m_sweep.c + r2;
	b2Vec2 d = p2 - p1;
	b2Vec2 axis = b1->GetWorldVector(m_localXAxis1);

	b2Vec2 v1 = b1->m_linearVelocity;
	b2Vec2 v2 = b2->m_linearVelocity;
	float32 w1 = b1->m_angularVelocity;
	float32 w2 = b2->m_angularVelocity;

	float32 speed = b2Dot(d, b2Cross(w1, axis)) + b2Dot(axis, v2 + b2Cross(w2, r2) - v1 - b2Cross(w1, r1));
	return speed;
}

bool b2LineJoint::IsLimitEnabled() const
{
	return m_enableLimit;
}

void b2LineJoint::EnableLimit(bool flag)
{
	m_body1->WakeUp();
	m_body2->WakeUp();
	m_enableLimit = flag;
}

float32 b2LineJoint::GetLowerLimit() const
{
	return m_lowerTranslation;
}

float32 b2LineJoint::GetUpperLimit() const
{
	return m_upperTranslation;
}

void b2LineJoint::SetLimits(float32 lower, float32 upper)
{
	b2Assert(lower <= upper);
	m_body1->WakeUp();
	m_body2->WakeUp();
	m_lowerTranslation = lower;
	m_upperTranslation = upper;
}

bool b2LineJoint::IsMotorEnabled() const
{
	return m_enableMotor;
}

void b2LineJoint::EnableMotor(bool flag)
{
	m_body1->WakeUp();
	m_body2->WakeUp();
	m_enableMotor = flag;
}

void b2LineJoint::SetMotorSpeed(float32 speed)
{
	m_body1->WakeUp();
	m_body2->WakeUp();
	m_motorSpeed = speed;
}

void b2LineJoint::SetMaxMotorForce(float32 force)
{
	m_body1->WakeUp();
	m_body2->WakeUp();
	m_maxMotorForce = B2FORCE_SCALE(float32(1.0))*force;
}

float32 b2LineJoint::GetMotorForce() const
{
	return m_motorImpulse;
}





