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

#ifndef STAR_H
#define STAR_H

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"
#include "Engine/Sprite.h"

class Star : public Box2DEntity
{
private :
    enum state {
        state_normal,
        state_invisible
    };

    state m_State;
    SDL_SurfacePtr m_pImage;
    float m_fLife;

    b2Vec2 m_StartPos;
    Sprite m_Sprite;
public:
    Star(b2World * pWorld, const b2Vec2 & startPos);
    virtual ~Star();

    void init();

    void update(float timeElapsed);
    void render();
    bool handleMessage(const Message & msg){return false;}

    bool done() { return m_fLife <= 0.0f; }
    std::string getType() { return "Star"; }

    void kill() { m_fLife = 0.0f; }

    void destructionAnim();
};

#endif // STAR_H
