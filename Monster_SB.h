/*
 * Survival
 *
 * Copyright (C) 2009-2011 Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
