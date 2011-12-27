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

#include "Effect.h"
#include "../Camera.h"

Effect::Effect(const b2Vec2 & pos)
: m_vPos(pos)
{
    //ctor
}

Effect::~Effect()
{
    //dtor
}

void Effect::render()
{
    b2Vec2 pos = m_vPos;
    transform_Camera(pos);
    m_Sprite.render(pos);
}

void Effect::update(float timeElapsed)
{
    m_Sprite.update(timeElapsed);

}

