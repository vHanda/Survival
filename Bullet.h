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

#ifndef BULLET_H
#define BULLET_H

#include "Projectile.h"

enum bullet_type {
    bullet_player =0,
    bullet_monster=1
};

class Bullet : public Projectile
{
private :
    bullet_type m_Type;
public:
    Bullet(Agent * a, bullet_type bt, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Bullet();

    virtual void init();

    std::string getType() { return "Bullet"; }
    virtual void destructionAnim();
};

#endif // BULLET_H
