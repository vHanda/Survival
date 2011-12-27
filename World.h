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
