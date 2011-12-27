#include "SteeringBehaviors.h"

SteeringBehaviors::SteeringBehaviors(b2Body * body, float maxSpeed)
:   m_pBody(body),
    m_fMaxSpeed(maxSpeed)
{
    m_fWanderRadius = 5;
    m_fWanderJitter = 0.5;
}

SteeringBehaviors::~SteeringBehaviors()
{
    //dtor
}

//Steering Behaviors
b2Vec2 SteeringBehaviors::seek(const b2Vec2 & targetPos)
{
    b2Vec2 desVelocity = targetPos - m_pBody->GetWorldCenter();
    desVelocity.Normalize();
    desVelocity *= m_fMaxSpeed;

    return desVelocity - m_pBody->GetLinearVelocity();
}

b2Vec2 SteeringBehaviors::flee(const b2Vec2 & targetPos)
{
    const float panicDistSq = 20*20;
    const b2Vec2 & pos = m_pBody->GetWorldCenter();

    if(b2DistanceSquared( pos, targetPos ) >= panicDistSq )
        return b2Vec2(0.0f, 0.0f);

    b2Vec2 desVelocity = m_pBody->GetWorldCenter() - targetPos;
    desVelocity.Normalize();
    desVelocity *= m_fMaxSpeed;

    return desVelocity - m_pBody->GetLinearVelocity();
}

//Persuit
b2Vec2 SteeringBehaviors::persuit(const b2Body * evader)
{
    b2Vec2 toEvader = evader->GetWorldCenter() - m_pBody->GetWorldCenter();
    b2Vec2 heading = m_pBody->GetLinearVelocity();
    heading.Normalize();

    float relativeHeading = b2Dot( heading, toEvader );
    float dot = b2Dot( toEvader, heading );

    if( dot > 0 && relativeHeading < -0.95)  //acos(0.95)=18 degs
    {
        return seek(evader->GetWorldCenter());
    }

    float lookAheadTime = toEvader.Length() /
                        (m_fMaxSpeed + evader->GetLinearVelocity().Length());

    //now seek to the predicted future position of the evader
    return seek(evader->GetWorldCenter() + (lookAheadTime*evader->GetLinearVelocity()) );
}

b2Vec2 SteeringBehaviors::evade(const b2Body * persuer)
{
    b2Vec2 toPersuer = persuer->GetWorldCenter() - m_pBody->GetWorldCenter();
    float lookAheadTime = toPersuer.Length() /
                        (m_fMaxSpeed + persuer->GetLinearVelocity().Length());

    //now  flee from the predicted future position of the evader
    return flee(persuer->GetWorldCenter() + (lookAheadTime*persuer->GetLinearVelocity()) );
}

b2Vec2 SteeringBehaviors::wander()
{
    b2Vec2 wanderTarget(0.0f, 0.0f);
    wanderTarget.x += randomClamped() * m_fWanderJitter;
    wanderTarget.y += randomClamped() * m_fWanderJitter;

    wanderTarget.Normalize();
    wanderTarget *= m_fWanderRadius;

    b2Vec2 targetLocal = m_pBody->GetLocalPoint(wanderTarget);
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    vel.Normalize();
    targetLocal += (m_fWanderRadius * vel);

    b2Vec2 targetWorld = m_pBody->GetWorldPoint(targetLocal);
    return targetWorld - m_pBody->GetWorldCenter();
    //Not tested ...
}

b2Vec2 SteeringBehaviors::obstacleAvoidance(b2Shape* array, int size)
{
    return b2Vec2(0.0f, 0.0f);
}

//Flocking
b2Vec2 SteeringBehaviors::seperation(std::vector<b2Body *> neighbours)
{
    const b2Vec2 & pos = m_pBody->GetWorldCenter();
    b2Vec2 steeringForce(0.0f, 0.0f);
    for(unsigned int i=0; i<neighbours.size(); i++)
    {
        if(neighbours[i] == m_pBody)
            continue;

        b2Vec2 toAgent = pos - neighbours[i]->GetWorldCenter();
        float length = toAgent.Length();
        toAgent.Normalize();
        toAgent *= 1.0/length; //Cause there is no /= operator.

        steeringForce += toAgent;
    }
    return steeringForce;
}

b2Vec2 SteeringBehaviors::alignment(std::vector<b2Body *> neighbours)
{
    b2Vec2 averageHeading(0.0f, 0.0f);
    int num =0;
    for(unsigned int i=0; i<neighbours.size(); i++)
    {
        if(neighbours[i] == m_pBody)
            continue;

        b2Vec2 vel = neighbours[i]->GetLinearVelocity();
        vel.Normalize();

        averageHeading += vel;
        num ++;
    }

    averageHeading *= 1.0/num;

    b2Vec2 vel = m_pBody->GetLinearVelocity();
    vel.Normalize();

    averageHeading -= vel;
    return averageHeading;
}

b2Vec2 SteeringBehaviors::cohesion(std::vector<b2Body *> neighbours)
{
    b2Vec2 centerOfMass(0.0f, 0.0f);
    int num=0;
    for(unsigned int i=0; i<neighbours.size(); i++)
    {
        if(neighbours[i] == m_pBody)
            continue;

        b2Vec2 pos = neighbours[i]->GetWorldCenter();
        centerOfMass += pos;
        num++;
    }
    centerOfMass *= 1.0/num;
    return seek(centerOfMass);
}

b2Vec2 SteeringBehaviors::projectileAvoidance(std::vector<b2Body *> proj)
{
    b2Vec2 force(0.0f, 0.0f);
    for(unsigned int i=0; i<proj.size(); i++)
    {
        b2Vec2 f = evade(proj[i]);
        //f *= 1.0;
        force += f;
    }
    return force;
}
