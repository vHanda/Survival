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

#include "Obstacle.h"
#include <SDL/SDL_rotozoom.h>

void Obstacle::init()
{
    std::string fileName = "data/gfx/s";
    fileName += '1' + rand() % 2;
    fileName += ".png";
    m_pImage = load_image(fileName);

    //Box2D
    b2BodyDef bodyDef;
    bodyDef.position = m_StartPos;
    bodyDef.userData = this;

    b2CircleDef shapeDef;
    shapeDef.radius = (m_pImage->w / World::ratio) / 2.5;
    shapeDef.restitution = 1.0;
    shapeDef.density = 5.0;

    m_pBody = m_pWorld->CreateBody(&bodyDef);
    m_pBody->CreateShape(&shapeDef);

    m_pImage = rotozoomSurface(m_pImage.get(), rand()%360, 1.0, 1);
}

void Obstacle::deinit()
{
    if(m_pBody != NULL)
    {
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}

void Obstacle::render()
{
    render_Box2DEntity(m_pImage.get(), m_pBody);
}

void Obstacle::update(float timeElapsed)
{

}
