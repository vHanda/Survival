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

#ifndef SHIELD_H
#define SHIELD_H

#include "Projectile.h"

enum shield_type {
    shield_player =0,
    shield_monster
};

class Shield : public Projectile
{
private :
    shield_type m_Type;
public:
    Shield(Agent * a, shield_type st, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Shield();

    virtual void init();

    std::string getType() { return "Shield"; }
    virtual void destructionAnim();
};

#endif // SHIELD_H
