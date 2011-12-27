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

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"

class Agent;

class Projectile : public Box2DEntity
{
protected :
    SDL_SurfacePtr m_pImage;

    b2Vec2 m_StartPos;
    b2Vec2 m_Dir;

    float m_fSpeed;
    float m_fLife;
    float m_fDamage;

    Agent * m_pOwner;

    void initFromFile(const std::string & fileName);
public:
    Projectile(Agent * a, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Projectile();

    virtual void init();

    virtual void update(float timeElapsed);
    virtual void render();
    virtual bool handleMessage(const Message & msg) {return false;}

    //Life controlling
    virtual bool done() const { return m_fLife <= 0.0f; }
    virtual void kill() { m_fLife = 0.0f; }

    void resetOwner()   { m_pOwner = NULL; }

    float getDamage()   const { return m_fDamage; }
    Agent * getOwner()  const { return m_pOwner; }

    virtual void destructionAnim() = 0;
};

#endif // PROJECTILE_H
