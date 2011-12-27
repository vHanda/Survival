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

#ifndef OBSTACLE_INCLUDED
#define OBSTACLE_INCLUDED

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"

class Obstacle : public Box2DEntity {
private :
    SDL_SurfacePtr m_pImage;
    b2Vec2 m_StartPos;
public :
    Obstacle(b2World * pWorld, const b2Vec2 & startPos)
    : Box2DEntity(pWorld), m_StartPos(startPos) {}
    ~Obstacle() { deinit(); }

    void init();
    void deinit();

    void update(float timeElapsed);
    void render();

    std::string getType() { return "Obstacle"; }
    bool handleMessage(const Message & msg)
    { return false; }
};

#endif // OBSTACLE_INCLUDED
