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

#include "Dynamics/b2Body.h"
#include "Dynamics/b2World.h"
#include "Dynamics/Joints/b2Joint.h"
#include "Collision/Shapes/b2Shape.h"
#include "Collision/Shapes/b2EdgeShape.h"

b2Body::b2Body(const b2BodyDef* bd, b2World* world)
{
	b2Assert(world->m_lock == false);

	m_flags = 0;

	if (bd->isBullet)
	{
		m_flags |= e_bulletFlag;
	}
	if (bd->fixedRotation)
	{
		m_flags |= e_fixedRotationFlag;
	}
	if (bd->allowSleep)
	{
		m_flags |= e_allowSleepFlag;
	}
	if (bd->isSleeping)
	{
		m_flags |= e_sleepFlag;
	}

	m_world = world;

	m_xf.position = bd->position;
	m_xf.R.Set(bd->angle);

	m_sweep.localCenter = bd->massData.center;
	m_sweep.t0 = 1.0f;
	m_sweep.a0 = m_sweep.a = bd->angle;
	m_sweep.c0 = m_sweep.c = b2Mul(m_xf, m_sweep.localCenter);

	m_jointList = NULL;
	m_contactList = NULL;
	m_controllerList = NULL;
	m_prev = NULL;
	m_next = NULL;

	m_linearDamping = bd->linearDamping;
	m_angularDamping = bd->angularDamping;

	m_force.Set(0.0f, 0.0f);
	m_torque = 0.0f;

	m_linearVelocity.SetZero();
	m_angularVelocity = 0.0f;

	m_sleepTime = 0.0f;

	m_invMass = 0.0f;
	m_I = 0.0f;
	m_invI = 0.0f;

	m_mass = bd->massData.mass;

	if (m_mass > 0.0f)
	{
		m_invMass = 1.0f / m_mass;
	}

	if ((m_flags & b2Body::e_fixedRotationFlag) == 0)
	{
		m_I = bd->massData.I;
	}
	
	if (m_I > 0.0f)
	{
		m_invI = 1.0f / m_I;
	}

	if (m_invMass == 0.0f && m_invI == 0.0f)
	{
		m_type = e_staticType;
	}
	else
	{
		m_type = e_dynamicType;
	}

	m_userData = bd->userData;

	m_shapeList = NULL;
	m_shapeCount = 0;
}

b2Body::~b2Body()
{
	b2Assert(m_world->m_lock == false);
	// shapes and joints are destroyed in b2World::Destroy
}


float32 connectEdges(b2EdgeShape * const & s1, b2EdgeShape * const & s2, float32 angle1)
{
	float32 angle2 = b2Atan2(s2->GetDirectionVector().y, s2->GetDirectionVector().x);
	b2Vec2 core = tanf((angle2 - angle1) * 0.5f) * s2->GetDirectionVector();
	core = b2_toiSlop * (core - s2->GetNormalVector()) + s2->GetVertex1();
	b2Vec2 cornerDir = s1->GetDirectionVector() + s2->GetDirectionVector();
	cornerDir.Normalize();
	bool convex = b2Dot(s1->GetDirectionVector(), s2->GetNormalVector()) > 0.0f;
	s1->SetNextEdge(s2, core, cornerDir, convex);
	s2->SetPrevEdge(s1, core, cornerDir, convex);
	return angle2;
}

b2Shape* b2Body::CreateShape(b2ShapeDef* def)
{
	b2Assert(m_world->m_lock == false);
	if (m_world->m_lock == true)
	{
		return NULL;
	}
	
	
	// TODO: Decide on a better place to initialize edgeShapes. (b2Shape::Create() can't
	//       return more than one shape to add to parent body... maybe it should add
	//       shapes directly to the body instead of returning them?)
	if (def->type == e_edgeShape) {
		b2EdgeChainDef* edgeDef = (b2EdgeChainDef*)def;
		b2Vec2 v1;
		b2Vec2 v2;
		int i;
		
		if (edgeDef->isALoop) {
			v1 = edgeDef->vertices[edgeDef->vertexCount-1];
			i = 0;
		} else {
			v1 = edgeDef->vertices[0];
			i = 1;
		}
		
		b2EdgeShape* s0 = NULL;
		b2EdgeShape* s1 = NULL;
		b2EdgeShape* s2 = NULL;
		float32 angle = 0.0f;
		for (; i < edgeDef->vertexCount; i++) {
			v2 = edgeDef->vertices[i];
			
			void* mem = m_world->m_blockAllocator.Allocate(sizeof(b2EdgeShape));
			s2 = new (mem) b2EdgeShape(v1, v2, def);
			s2->m_next = m_shapeList;
			m_shapeList = s2;
			++m_shapeCount;
			s2->m_body = this;
			s2->CreateProxy(m_world->m_broadPhase, m_xf);
			s2->UpdateSweepRadius(m_sweep.localCenter);
			
			if (s1 == NULL) {
				s0 = s2;
				angle = b2Atan2(s2->GetDirectionVector().y, s2->GetDirectionVector().x);
			} else {
				angle = connectEdges(s1, s2, angle);
			}
			s1 = s2;
			v1 = v2;
		}
		if (edgeDef->isALoop) connectEdges(s1, s0, angle);
		return s0;
	}
	
	b2Shape* s = b2Shape::Create(def, &m_world->m_blockAllocator);

	s->m_next = m_shapeList;
	m_shapeList = s;
	++m_shapeCount;

	s->m_body = this;

	// Add the shape to the world's broad-phase.
	s->CreateProxy(m_world->m_broadPhase, m_xf);

	// Compute the sweep radius for CCD.
	s->UpdateSweepRadius(m_sweep.localCenter);

	return s;
}

void b2Body::DestroyShape(b2Shape* s)
{
	b2Assert(m_world->m_lock == false);
	if (m_world->m_lock == true)
	{
		return;
	}

	b2Assert(s->GetBody() == this);
	s->DestroyProxy(m_world->m_broadPhase);

	b2Assert(m_shapeCount > 0);
	b2Shape** node = &m_shapeList;
	bool found = false;
	while (*node != NULL)
	{
		if (*node == s)
		{
			*node = s->m_next;
			found = true;
			break;
		}

		node = &(*node)->m_next;
	}

	// You tried to remove a shape that is not attached to this body.
	b2Assert(found);

	s->m_body = NULL;
	s->m_next = NULL;

	--m_shapeCount;

	b2Shape::Destroy(s, &m_world->m_blockAllocator);
}

// TODO_ERIN adjust linear velocity and torque to account for movement of center.
void b2Body::SetMass(const b2MassData* massData)
{
	b2Assert(m_world->m_lock == false);
	if (m_world->m_lock == true)
	{
		return;
	}

	m_invMass = 0.0f;
	m_I = 0.0f;
	m_invI = 0.0f;

	m_mass = massData->mass;

	if (m_mass > 0.0f)
	{
		m_invMass = 1.0f / m_mass;
	}

	if ((m_flags & b2Body::e_fixedRotationFlag) == 0)
	{
		m_I = massData->I;
	}

	if (m_I > 0.0f)
	{
		m_invI = 1.0f / m_I;
	}

	// Move center of mass.
	m_sweep.localCenter = massData->center;
	m_sweep.c0 = m_sweep.c = b2Mul(m_xf, m_sweep.localCenter);

	// Update the sweep radii of all child shapes.
	for (b2Shape* s = m_shapeList; s; s = s->m_next)
	{
		s->UpdateSweepRadius(m_sweep.localCenter);
	}

	int16 oldType = m_type;
	if (m_invMass == 0.0f && m_invI == 0.0f)
	{
		m_type = e_staticType;
	}
	else
	{
		m_type = e_dynamicType;
	}

	// If the body type changed, we need to refilter the broad-phase proxies.
	if (oldType != m_type)
	{
		for (b2Shape* s = m_shapeList; s; s = s->m_next)
		{
			s->RefilterProxy(m_world->m_broadPhase, m_xf);
		}
	}
}

// TODO_ERIN adjust linear velocity and torque to account for movement of center.
void b2Body::SetMassFromShapes()
{
	b2Assert(m_world->m_lock == false);
	if (m_world->m_lock == true)
	{
		return;
	}

	// Compute mass data from shapes. Each shape has its own density.
	m_mass = 0.0f;
	m_invMass = 0.0f;
	m_I = 0.0f;
	m_invI = 0.0f;

	b2Vec2 center = b2Vec2_zero;
	for (b2Shape* s = m_shapeList; s; s = s->m_next)
	{
		b2MassData massData;
		s->ComputeMass(&massData);
		m_mass += massData.mass;
		center += massData.mass * massData.center;
		m_I += massData.I;
	}

	// Compute center of mass, and shift the origin to the COM.
	if (m_mass > 0.0f)
	{
		m_invMass = 1.0f / m_mass;
		center *= m_invMass;
	}

	if (m_I > 0.0f && (m_flags & e_fixedRotationFlag) == 0)
	{
		// Center the inertia about the center of mass.
		m_I -= m_mass * b2Dot(center, center);
		b2Assert(m_I > 0.0f);
		m_invI = 1.0f / m_I;
	}
	else
	{
		m_I = 0.0f;
		m_invI = 0.0f;
	}

	// Move center of mass.
	m_sweep.localCenter = center;
	m_sweep.c0 = m_sweep.c = b2Mul(m_xf, m_sweep.localCenter);

	// Update the sweep radii of all child shapes.
	for (b2Shape* s = m_shapeList; s; s = s->m_next)
	{
		s->UpdateSweepRadius(m_sweep.localCenter);
	}

	int16 oldType = m_type;
	if (m_invMass == 0.0f && m_invI == 0.0f)
	{
		m_type = e_staticType;
	}
	else
	{
		m_type = e_dynamicType;
	}

	// If the body type changed, we need to refilter the broad-phase proxies.
	if (oldType != m_type)
	{
		for (b2Shape* s = m_shapeList; s; s = s->m_next)
		{
			s->RefilterProxy(m_world->m_broadPhase, m_xf);
		}
	}
}

bool b2Body::SetXForm(const b2Vec2& position, float32 angle)
{
	b2Assert(m_world->m_lock == false);
	if (m_world->m_lock == true)
	{
		return true;
	}

	if (IsFrozen())
	{
		return false;
	}

	m_xf.R.Set(angle);
	m_xf.position = position;

	m_sweep.c0 = m_sweep.c = b2Mul(m_xf, m_sweep.localCenter);
	m_sweep.a0 = m_sweep.a = angle;

	bool freeze = false;
	for (b2Shape* s = m_shapeList; s; s = s->m_next)
	{
		bool inRange = s->Synchronize(m_world->m_broadPhase, m_xf, m_xf);

		if (inRange == false)
		{
			freeze = true;
			break;
		}
	}

	if (freeze == true)
	{
		m_flags |= e_frozenFlag;
		m_linearVelocity.SetZero();
		m_angularVelocity = 0.0f;
		for (b2Shape* s = m_shapeList; s; s = s->m_next)
		{
			s->DestroyProxy(m_world->m_broadPhase);
		}

		// Failure
		return false;
	}

	// Success
	m_world->m_broadPhase->Commit();
	return true;
}

bool b2Body::SynchronizeShapes()
{
	b2XForm xf1;
	xf1.R.Set(m_sweep.a0);
	xf1.position = m_sweep.c0 - b2Mul(xf1.R, m_sweep.localCenter);

	bool inRange = true;
	for (b2Shape* s = m_shapeList; s; s = s->m_next)
	{
		inRange = s->Synchronize(m_world->m_broadPhase, xf1, m_xf);
		if (inRange == false)
		{
			break;
		}
	}

	if (inRange == false)
	{
		m_flags |= e_frozenFlag;
		m_linearVelocity.SetZero();
		m_angularVelocity = 0.0f;
		for (b2Shape* s = m_shapeList; s; s = s->m_next)
		{
			s->DestroyProxy(m_world->m_broadPhase);
		}

		// Failure
		return false;
	}

	// Success
	return true;
}
