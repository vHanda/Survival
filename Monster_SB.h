//Monster Steering Behaviors

#ifndef MONSTER_SB_H
#define MONSTER_SB_H

#include "SteeringBehaviors.h"

class Monster;
class Player;
class Map;

class Monster_SB : public SteeringBehaviors
{
protected :
    Monster * m_pMonster;
    Map * m_pMap;
    Player * m_pPlayer;
    b2World * m_pWorld;

public:
    Monster_SB(Monster * pM);
    virtual ~Monster_SB();

    //Steering Behaviors
    b2Vec2 persuit();
    b2Vec2 evade();
    b2Vec2 obstacleAvoidance();
    b2Vec2 projectileAvoidance();

    //Flocking
    void flocking(b2Vec2 & seper, b2Vec2 & align, b2Vec2 & cohes);
};

#endif // MONSTER_SB_H
