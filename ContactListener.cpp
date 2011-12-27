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

#include "ContactListener.h"
#include "Bullet.h"
#include "Shield.h"
#include "Agent.h"
#include "Star.h"
#include "Player.h"
#include "Engine/Managers/EffectManager.h"

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::Add(const b2ContactPoint *point)
{
    void * userData1 = point->shape1->GetBody()->GetUserData();
    void * userData2 = point->shape2->GetBody()->GetUserData();

    if( userData1 == NULL && userData2 == NULL )
        return;

    //If one is a Bullet and the other contains no user Data(Map Bounderies)
    if( userData2 == NULL )
    {
        Entity * ent1 = (Entity*)userData1;
        if( ent1->getType() == "Bullet" )
        {
            Bullet * b = dynamic_cast<Bullet *>(ent1);
            handle_Bullet_Obstacle(b);
            return;
        }
    }

    if( userData1 == NULL )
    {
        Entity * ent2 = (Entity*)userData2;
        if( ent2->getType() == "Bullet" )
        {
            Bullet * b = dynamic_cast<Bullet *>(ent2);
            handle_Bullet_Obstacle(b);
            return;
        }
    }

    //Normal stuff
    if( userData1 == NULL || userData2 == NULL )
        return;

    Entity * ent1 = (Entity*)userData1;
    Entity * ent2 = (Entity*)userData2;

    //For all permutations of Bullet, Shield and Agent.

    //Bullet and others
    if( ent1->getType() == "Bullet" )
    {
        //Bullet and Bullet
        if(ent2->getType() == "Bullet" )
        {
            Bullet * b1 = dynamic_cast<Bullet *>(ent1);
            Bullet * b2 = dynamic_cast<Bullet *>(ent2);

            handle_Bullet_Bullet( b1, b2 );
            return;
        }

        //Bullet & Shield
        if(ent2->getType() == "Shield" )
        {
            Bullet * b = dynamic_cast<Bullet *>(ent1);
            Shield * s = dynamic_cast<Shield *>(ent2);

            handle_Bullet_Shield( b, s);
            return;
        }

        //Bullet & Agent
        if(ent2->getType() == "Agent" )
        {
            Bullet * b = dynamic_cast<Bullet *>(ent1);
            Agent * a = dynamic_cast<Agent *>(ent2);

            handle_Agent_Bullet( a, b);
            return;
        }
    }

    //Shield and others
    if( ent1->getType() == "Shield" )
    {
        //Shield  & Bullet
        if(ent2->getType() == "Bullet")
        {
            Bullet * b = dynamic_cast<Bullet *>(ent2);
            Shield * s = dynamic_cast<Shield *>(ent1);

            handle_Bullet_Shield( b, s );
            return;
        }

        //Shield and Shield
        if(ent2->getType() == "Shield" )
        {
            Shield * s1 = dynamic_cast<Shield *>(ent1);
            Shield * s2 = dynamic_cast<Shield *>(ent2);

            handel_Shield_Shield(s1,s2);
            return;
        }

        //Shield and Agent
        if(ent2->getType() == "Agent" )
        {
            Shield * s = dynamic_cast<Shield *>(ent1);
            Agent * a = dynamic_cast<Agent *>(ent2);

            handle_Agent_Shield(a,s);
            return;
        }
    }

    //Agent and others
    if( ent1->getType() == "Agent")
    {
        //Agent and Bullet
        if(ent2->getType() == "Bullet")
        {
            Bullet * b = dynamic_cast<Bullet *>(ent2);
            Agent * a = dynamic_cast<Agent *>(ent1);

            handle_Agent_Bullet( a, b);
            return;
        }

        //Agent and Shield
        if(ent2->getType() == "Shield")
        {
            Shield * s = dynamic_cast<Shield *>(ent2);
            Agent * a = dynamic_cast<Agent *>(ent1);

            handle_Agent_Shield(a,s);
            return;
        }

        //Agent and Agent
        if(ent2->getType() == "Agent")
        {
            Agent * a1 = dynamic_cast<Agent *>(ent1);
            Agent * a2 = dynamic_cast<Agent *>(ent2);

            handle_Agent_Agent(a1, a2, point->position);
            return;
        }

        //Agent and Star
        if(ent2->getType() == "Star")
        {
            Agent * a = dynamic_cast<Agent *>(ent1);
            Star * s = dynamic_cast<Star *>(ent2);

            handle_Agent_Star(a,s);
            return;
        }
    }

    //Star and Agent
    if( ent1->getType() == "Star" && ent2->getType() == "Agent")
    {
        Agent * a = dynamic_cast<Agent *>(ent2);
        Star * s = dynamic_cast<Star *>(ent1);

        handle_Agent_Star(a,s);
        return;
    }

    //Bullet and Obstacle
    if( ent1->getType() == "Bullet" && ent2->getType() == "Obstacle" )
    {
        Bullet * b = dynamic_cast<Bullet *>(ent1);
        handle_Bullet_Obstacle(b);
        return;
    }

    //Obstacle and Bullet
    if( ent2->getType() == "Bullet" && ent1->getType() == "Obstacle" )
    {
        Bullet * b = dynamic_cast<Bullet *>(ent2);
        handle_Bullet_Obstacle(b);
        return;
    }
}

void handle_Bullet_Bullet(Bullet * b1, Bullet * b2)
{
    if( b1->getOwner() == b2->getOwner() )
        return;

    b1->kill();
    b2->kill();

    b1->destructionAnim();
    b2->destructionAnim();
}

void handle_Bullet_Shield(Bullet * b, Shield * s)
{

    b->resetOwner();
    //TODO : Add boundcing sound effect
}

void handle_Agent_Shield(Agent * a, Shield * s)
{
    a->handleProjectile(s);
    s->kill();
    s->destructionAnim();
}

void handle_Agent_Bullet(Agent * a, Bullet * b)
{
    a->handleProjectile(b);
    b->kill();
    b->destructionAnim();
}

void handle_Agent_Agent(Agent * a1, Agent * a2, const b2Vec2 & pos)
{
    if( !a1->isPlayer() && !a2->isPlayer() )
        return;

    float a1Life = a1->getLife();
    float a2Life = a2->getLife();

    if(a1Life < 0 || a2Life < 0 )
        return;

    a1->reduceLife(a2Life);
    a2->reduceLife(a1Life);
}

void handle_Bullet_Obstacle(Bullet *b)
{
    b->kill();
    b->destructionAnim();
}

void handel_Shield_Shield(Shield * s1, Shield * s2)
{
    s1->kill();
    s2->kill();

    s1->destructionAnim();
    s2->destructionAnim();
}

void handle_Agent_Star(Agent * a, Star *s)
{
    if( a->isPlayer() )
    {
        Player * p = dynamic_cast<Player *>(a);
        p->addStar();
        s->kill();
        s->destructionAnim();
    }
}
