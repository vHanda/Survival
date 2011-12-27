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

#ifndef WORLD_H
#define WORLD_H

#include "Box2D/Box2D.h"

class World {
private :
    World();
    ~World();
public :
    /*static b2World * getInstance()
    {
        b2AABB worldAABB;
        worldAABB.lowerBound.Set(-200.0f, -200.0f);
        worldAABB.upperBound.Set(200.0f, 200.0f);

        b2Vec2 gravity(0.0f, 0.0f);
        bool doSleep = true;

        static b2World world(worldAABB, gravity, doSleep);
        return &world;
    }*/
    static const float ratio = 25;

    /*
    static void reset()
    {
        b2World * pWorld = World::getInstance();
        b2Body* b = pWorld->GetBodyList();
        while( b != NULL )
        {
            b2Body * p = b;
            b = b->GetNext();
            pWorld->DestroyBody( p );
        }
    }*/
};

//#define gWorld World::getInstance()

#endif
