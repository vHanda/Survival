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

#include "Map.h"
#include <iostream>
#include "Camera.h"
#include "World.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <algorithm>
#include <functional>
#include "Bullet.h"
#include "Shield.h"
#include "Star.h"
#include "Obstacle.h"
#include "Engine/Engine.h"
#include "Image/PerlinNoise.h"
#include "Image/Fog.h"
#include <boost/bind.hpp>

Map::Map(b2World * pWorld)
: m_pWorld(pWorld)
{
    //ctor
}

Map::~Map()
{
    deinit();
}

void Map::init()
{
    m_pSurface = load_image("data/gfx/map.png");
    //SDL_FillRect(m_pSurface.get(), 0, 0xFFFFFFFF);
    //m_pSurface = Render_Clouds(800,600, 19.0, .5, 128, 190, 200 );
    //m_pSurface = SDL_CreateRGBSurface( 800*4, 600*4 );
    //Color c(240, 120, 60);
    //Fog f(c, 1.0);
    //f(m_pSurface.get());
    //PerlinNoise pn( 1+rand()%10, 1.0/rand(), 15.0, rand() );
    //pn(m_pSurface.get());

    m_iWidth = m_pSurface->w / World::ratio;
    m_iHeight = m_pSurface->h / World::ratio;

    createMapBounderies();
    createMap();
}

void Map::deinit()
{
    m_Bullets.clear();
    m_Shields.clear();
    m_Stars.clear();
    m_Obstacles.clear();
}

void Map::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_Rect rect = Camera::getInstance()->getRect();
    SDL_BlitSurface( m_pSurface.get(), &rect, screen, NULL );

    //Rendering Entities
    std::for_each( m_Bullets.begin(), m_Bullets.end(), std::mem_fun_ref( &Bullet::render ));
    std::for_each( m_Shields.begin(), m_Shields.end(), std::mem_fun_ref( &Shield::render ));
    std::for_each( m_Stars.begin(), m_Stars.end(), std::mem_fun_ref( &Star::render ));
    std::for_each( m_Obstacles.begin(), m_Obstacles.end(), std::mem_fun_ref( &Obstacle::render ));
}

void Map::update(float timeElapsed)
{
    //Bullets
    std::for_each(  m_Bullets.begin(), m_Bullets.end(),
                    boost::bind(&Bullet::update, _1, timeElapsed) );
    m_Bullets.erase_if( std::mem_fun_ref(& Bullet::done ) );

    //Shields
    std::for_each(  m_Shields.begin(), m_Shields.end(),
                    boost::bind(&Shield::update, _1, timeElapsed) );
    m_Shields.erase_if( std::mem_fun_ref(& Shield::done ) );

    //Stars
    std::for_each(  m_Stars.begin(), m_Stars.end(),
                    boost::bind(&Star::update, _1, timeElapsed) );
    m_Stars.erase_if( std::mem_fun_ref(& Star::done ) );

    //Obstacles
    std::for_each(  m_Obstacles.begin(), m_Obstacles.end(),
                    boost::bind(&Obstacle::update, _1, timeElapsed) );

}

void Map::addBullet(Bullet * b)
{
    assert( b!=NULL);
    m_Bullets.push_back(b);
}

void Map::addShield(Shield * s)
{
    assert( s!=NULL );
    m_Shields.push_back(s);
}

void Map::addStar(Star * s)
{
    assert( s!=NULL );
    m_Stars.push_back(s);
}

void Map::createMap()
{
    //TODO : Add a quadrant system
    const int w = m_pSurface->w / World::ratio;
    const int h = m_pSurface->h / World::ratio;

    b2Vec2 oldPos(0.0f,0.f);
    const float minDis = 3;
    for(unsigned int i=0; i<16*5; i++)
    {
        bool foundPos = false;
        while(foundPos == false)
        {
            b2Vec2 pos(rand()%w, rand()%h);
            if(b2DistanceSquared(pos, oldPos) >= minDis)
            {
                foundPos = true;
                oldPos = pos;
            }
        }

        Obstacle * obs = new Obstacle(m_pWorld, oldPos);
        obs->init();

        m_Obstacles.push_back(obs);
    }

}

void Map::createMapBounderies()
{
    //Left
    b2BodyDef lbodyDef;
    lbodyDef.position = b2Vec2( -0.5, m_iHeight/2 );
    b2Body * plBody = m_pWorld->CreateBody(&lbodyDef);
    b2PolygonDef lshapeDef;
    lshapeDef.SetAsBox( 0.5, m_iHeight/2 );
    plBody->CreateShape(&lshapeDef);

    //Right
    b2BodyDef rbodyDef;
    rbodyDef.position = b2Vec2( m_iWidth + 0.5, m_iHeight/2 );
    b2Body * prBody = m_pWorld->CreateBody(&rbodyDef);
    b2PolygonDef rshapeDef;
    rshapeDef.SetAsBox( 0.5, m_iHeight/2 );
    prBody->CreateShape(&rshapeDef);

    //Up
    b2BodyDef ubodyDef;
    ubodyDef.position = b2Vec2( m_iWidth/2, -0.5 );
    b2Body * puBody = m_pWorld->CreateBody(&ubodyDef);
    b2PolygonDef ushapeDef;
    ushapeDef.SetAsBox( m_iWidth/2 , 0.5 );
    puBody->CreateShape(&ushapeDef);

    //Down
    b2BodyDef dbodyDef;
    dbodyDef.position = b2Vec2( m_iWidth/2, m_iHeight + 0.5 );
    b2Body * pdBody = m_pWorld->CreateBody(&dbodyDef);
    b2PolygonDef dshapeDef;
    dshapeDef.SetAsBox( m_iWidth/2 , 0.5 );
    pdBody->CreateShape(&dshapeDef);
}
