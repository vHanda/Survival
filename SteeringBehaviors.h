#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include <vector>
#include <Box2D/Box2D.h>

class SteeringBehaviors
{
protected :
    b2Body * m_pBody;
    float m_fMaxSpeed;
    float m_fWanderRadius;
    float m_fWanderJitter;

    float randomClamped() const
    { float r = (rand()%10000)/10000.0f; if(rand()%2) r*= -1; return r;}
public:
    SteeringBehaviors(b2Body * body, float maxSpeed);
    virtual ~SteeringBehaviors();

    b2Vec2 seek(const b2Vec2 & targetPos);
    b2Vec2 flee(const b2Vec2 & targetPos);
    b2Vec2 persuit(const b2Body * evader);
    b2Vec2 evade(const b2Body * persuer);
    b2Vec2 wander();
    b2Vec2 obstacleAvoidance(b2Shape* array, int size);
    b2Vec2 hide(const b2Body * target, b2Shape* array, int size);

    b2Vec2 projectileAvoidance(std::vector<b2Body *> proj);

    b2Vec2 seperation(std::vector<b2Body *> neighbours);
    b2Vec2 alignment(std::vector<b2Body *> neighbours);
    b2Vec2 cohesion(std::vector<b2Body *> neighbours);

};

#endif // STEERINGBEHAVIORS_H
