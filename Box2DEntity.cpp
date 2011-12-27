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

#include "Box2DEntity.h"
#include <SDL/SDL_rotozoom.h>
#include <cmath>
#include "World.h"

void Box2DEntity::adjustAngle(SDL_SurfacePtr & s)
{
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    if( vel == b2Vec2(0.0f, 0.0f) )
        return;

    vel.Normalize();
    const b2Vec2 up(0.0f, -1.0f);

    float dot = b2Dot( vel, up );
    float angle = acos(dot); //In Radians
    angle *= 180.0/b2_pi;
    if( vel.x > 0 )
        angle *= -1; //This is becuase the x-axis is being ignored in up

    float diff = angle - m_fAngle;
    if(diff == 0)
        return;

    if( abs(diff) < m_fMinAngle )
        return;

    //Rotate
    SDL_Surface * newSurface = rotozoomSurface( s.get(), diff, 1.0f, 10 );
    s = newSurface;
    m_fAngle += diff;

    //std::cout << "Vel : " << vel.x << " " << vel.y << std::endl;
    //std::cout << "\t" << angle << std::endl;
    //std::cout << diff << std::endl << std::endl;
}

void Box2DEntity::deinit()
{
    if(m_pBody != NULL)
    {
        //std::cout << "Deinit" << std::endl;
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}
