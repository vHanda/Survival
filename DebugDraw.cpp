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

#include "DebugDraw.h"
#include <iostream>
#include "World.h"
#include "Camera.h"

DebugDraw::DebugDraw()
{
    //ctor
    //std::cout << "Constructor - DebugDraw" << std::endl;
    //uint32 flags = b2DebugDraw::e_shapeBit;
    //SetFlags(flags);
}

DebugDraw::~DebugDraw()
{
    //std::cout << "Destructor - DebugDraw" << std::endl;
}


void DebugDraw::DrawPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_Rect r = Camera::getInstance()->getRect();
    for(int i=0; i < vertexCount; i++)
    {
        int k = (i == vertexCount-1) ? 0 : i+1;
        lineRGBA( screen,   vertices[i].x*World::ratio -r.x,
                            vertices[i].y*World::ratio -r.y,
                            vertices[k].x*World::ratio -r.x,
                            vertices[k].y*World::ratio -r.y,
                0, 255, 0, 255 );
    }
    //std::cout << "Drew Polygon" << std::endl;

}

void DebugDraw::DrawSolidPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    DrawPolygon( vertices, vertexCount, color);
    //std::cout << "Drew Solid Polygon" << std::endl;
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
    //std::cout << "Drawing Segment" << std::endl;
    lineRGBA( SDL_GetVideoSurface(), p1.x*World::ratio, p1.y*World::ratio,
                                     p2.x*World::ratio, p2.y*World::ratio,
            0, 0, 255, 255);
}
void DebugDraw::DrawCircle (const b2Vec2 &center, float32 radius, const b2Color &color)
{
    SDL_Rect r = Camera::getInstance()->getRect();
    circleRGBA( SDL_GetVideoSurface(), center.x*World::ratio -r.x, center.y*World::ratio -r.y,
                radius*World::ratio, 0, 0, 0, 255);
    //std::cout << "Drawing Solid Circle" << std::endl;*/
}

void DebugDraw::DrawSolidCircle (const b2Vec2 &center, float32 radius, const b2Vec2 &axis,const b2Color &color)
{
    SDL_Rect r = Camera::getInstance()->getRect();
    circleRGBA( SDL_GetVideoSurface(), center.x*World::ratio -r.x, center.y*World::ratio -r.y,
                radius*World::ratio, 0, 0, 0, 255);
}

void DebugDraw::DrawXForm (const b2XForm &xf)
{
     //std::cout << "Drawing XForm" << std::endl;
}
