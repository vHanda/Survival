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

#include "Monster_SB.h"
#include "Map.h"
#include "Monster.h"
#include "Player.h"
#include "Projectile.h"

Monster_SB::Monster_SB(Monster * pM)
:   SteeringBehaviors( pM->getBody(), pM->getSpeed() ),
    m_pMonster(pM)
{
    m_pMap = m_pMonster->getMap();
    m_pWorld = m_pMap->getWorld();
    m_pPlayer = m_pMonster->getPlayer();
}

Monster_SB::~Monster_SB()
{
}

b2Vec2 Monster_SB::persuit()
{
    return SteeringBehaviors::persuit( m_pPlayer->getBody() );
}

b2Vec2 Monster_SB::evade()
{
    return SteeringBehaviors::evade( m_pPlayer->getBody() );
}

b2Vec2 Monster_SB::obstacleAvoidance()
{
    assert(!!"Obstacle Avoidance not implemented !!");
    return b2Vec2(0.0f, 0.0f);
}

b2Vec2 Monster_SB::projectileAvoidance()
{
    b2Shape * shapes[25];
    b2Vec2 pos = m_pMonster->getBody()->GetWorldCenter();

    //Create AABB
    b2Vec2 topLeft = pos - b2Vec2(5, 5);
    b2Vec2 bottomRight = pos + b2Vec2(5, 5);
    if( topLeft.x > bottomRight.x && topLeft.y > bottomRight.y)
        std::swap(topLeft, bottomRight);
    b2AABB aabb;
    aabb.lowerBound = topLeft;
    aabb.upperBound = bottomRight;

    //Query World and get Shapes
    int size = m_pWorld->Query(aabb, shapes, 25);

    std::vector<b2Body *> proj;
    for(int i=0; i<size;i++)
    {
        b2Body * body = shapes[i]->GetBody();
        Box2DEntity * ent = (Box2DEntity *)body->GetUserData();
        if( ent == NULL )
            continue;
        if( ent->getType() == "Bullet" || ent->getType() == "Shield" )
        {
            Projectile * projectile = dynamic_cast<Projectile*>(ent);
            if( projectile->getOwner() == m_pMonster)
                continue;
            proj.push_back( body );
        }
    }

    return SteeringBehaviors::projectileAvoidance( proj );
}

void Monster_SB::flocking(b2Vec2 & seper, b2Vec2 & align, b2Vec2 & cohes)
{
    //Query neighbours
    b2Shape * shapes[25];
    b2Vec2 pos = m_pMonster->getBody()->GetWorldCenter();

    //Create AABB
    b2Vec2 topLeft = pos - b2Vec2(5, 5);
    b2Vec2 bottomRight = pos + b2Vec2(5,5);
    b2AABB aabb;
    aabb.lowerBound = topLeft;
    aabb.upperBound = bottomRight;

    //Query World and get Shapes
    int size = m_pWorld->Query(aabb, shapes, 25);

    std::vector<b2Body *> neighbours;
    for(int i=0; i<size; i++)
    {
        b2Body * body = shapes[i]->GetBody();
        void * userData = body->GetUserData();
        if( userData == NULL )
            continue;

        Entity * ent = static_cast<Entity *>(userData);
        if( ent->getType() == "Agent" )
        {
            Agent * agent = dynamic_cast<Agent *>(ent);
            if(agent->isPlayer() == true)
                continue;
            neighbours.push_back(body);
        }
    }
    seper = seperation( neighbours );
    align = alignment( neighbours );
    cohes = cohesion( neighbours );
}

