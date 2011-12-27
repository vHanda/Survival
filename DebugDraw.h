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

#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "Box2D/Box2D.h"
#include <SDL/SDL_gfxPrimitives.h>

class DebugDraw : public b2DebugDraw
{
public:
    DebugDraw();
    virtual ~DebugDraw();

    virtual void DrawPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    virtual void DrawSolidPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    virtual void DrawCircle (const b2Vec2 &center, float32 radius, const b2Color &color);
    virtual void DrawSolidCircle (const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
    virtual void DrawSegment (const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
    virtual void DrawXForm (const b2XForm &xf);
protected:
private:
};

#endif // DEBUGDRAW_H
