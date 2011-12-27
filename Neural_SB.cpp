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

#include "Neural_SB.h"
#include "Monster.h"
#include "Player.h"

Neural_SB::Neural_SB(Monster * m, NN_File * pBrain)
: Monster_SB(m), m_pBrain(pBrain)
{
    m_Input.resize(4);
    m_Output.resize(5);
    m_fMaxForce = m->getSpeed() * 100;
}

Neural_SB::~Neural_SB()
{
}

void Neural_SB::update(float timeElapsed)
{
    getInput();

    m_pBrain->run( m_Input, m_Output );

    b2Vec2 f = getForce();
    f *= timeElapsed;
    //std::cout << "\tForce : " << f.x << " " << f.y << std::endl;

    b2Vec2 vel = m_pMonster->getBody()->GetLinearVelocity();
    vel += f; //Mass is ignored
    m_pMonster->getBody()->SetLinearVelocity(vel);


    //Firing
    float bullet_fire = (rand()%100)/100.0;
    if( bullet_fire <= m_Output[ o_fire_bullet ] )
        m_pMonster->fireBullet();

    float shield_fire = (rand()%100)/100.0;
    if( shield_fire <= m_Output[ o_fire_shield ] )
        m_pMonster->fireShield();
}

void Neural_SB::getInput()
{
    b2Vec2 monsterPos = m_pMonster->getBody()->GetWorldCenter();
    b2Vec2 playerPos = m_pPlayer->getBody()->GetWorldCenter();
    b2Vec2 dist = monsterPos - playerPos;

    m_Input[ i_life ] = m_pMonster->getPercentLife();
    m_Input[ i_plr_dist ] = dist.Length() / 120.0; //Max width is 3200/25 .. 3000/25 = 120
    m_Input[ i_plr_life ] = m_pPlayer->getPercentLife();

    if(m_pPlayer->killed() != 0)
        m_Input[ i_killed ] = m_pPlayer->killed() / 50.0;
    else
        m_Input[ i_killed ] = 0.1;


    //std::cout << "Input : ";
    for(unsigned int i=0; i<m_Input.size(); i++)
    {
        //std::cout << m_Input[i] << " ";
        if(m_Input[i] > 1.0)
            m_Input[i] = 1.0;
    }
    //std::cout << std::endl;
}

b2Vec2 Neural_SB::getForce()
{
    b2Vec2 totForce(0.0f, 0.0f);
    b2Vec2 force;

    //Projectile Avoidance
    force = projectileAvoidance();
    if( accumForce(totForce, force) == false )
        return totForce;

    //Obstacle Avoidance
    //TODO

    //Persuit
    force = persuit();
    //for(unsigned int i=0; i<m_Output.size(); i++)
    //    std::cout << m_Output[ i ] << " ";
    //std::cout << std::endl;

    force *= m_Output[ o_persuit ] * 5;
    if( accumForce(totForce, force) == false )
        return totForce;

    //std::cout << "\t\tPersuit Force : " << totForce.x << " " << totForce.y << std::endl;

    //Evade
    force = evade();
    force *= m_Output[ o_evade ] * 5;
    if( accumForce(totForce, force) == false )
        return totForce;

    //std::cout << "\t\tEvade Force : " << totForce.x << " " << totForce.y << std::endl;

    //Flocking
    /*
    b2Vec2 cohes, align, sep;
    flocking( sep, align, cohes );

    cohes *= 0.5 * m_Output[ o_flocking ] * 5;
    align *= 0.5 * m_Output[ o_flocking ] * 5;
    sep *= 0.5 * m_Output[ o_flocking ] * 5;

    if( accumForce(totForce, cohes) == false )
        return totForce;

    if( accumForce(totForce, align) == false )
        return totForce;

    if( accumForce(totForce, sep) == false )
        return totForce;
    */

    //std::cout << "\t\tTotalForce : " << totForce.x << " " << totForce.y << std::endl;
    return totForce;
}

bool Neural_SB::accumForce(b2Vec2 & totForce, b2Vec2 force) const
{
    //std::cout << "\t\tTotalForce : " << totForce.x << " " << totForce.y << std::endl;
    b2Vec2 tot = totForce + force;
    if( tot.LengthSquared() <= m_fMaxForce*m_fMaxForce )
    {
        totForce += force;
        return true;
    }

    force.Normalize();
    force *= abs(m_fMaxForce - totForce.Length());
    totForce += force;
    return false;
}
