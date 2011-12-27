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

#include "Bullet.h"
#include "World.h"
#include "Engine/ErrorHandler.h"
#include "tinyxml/tinyxml.h"
#include "Monster.h"
#include "Engine/Managers/EffectManager.h"

Bullet::Bullet(Agent * a, bullet_type bt, const b2Vec2 & startPos, const b2Vec2 & dir)
: Projectile(a, startPos, dir), m_Type(bt)
{ }

Bullet::~Bullet()
{
    //deinit();
}

void Bullet::init()
{
    std::string fileName;
    switch( static_cast<int>(m_Type) )
    {
    case bullet_player :
        //Add a certain amount of Randomness
        m_Dir.x += (rand() % 1000)/10000.00f;
        m_Dir.y += (rand() % 1000)/10000.00f;

        fileName = "data/bullet_player";
        initFromFile(fileName);
        break;
    case bullet_monster :
        fileName = "data/bullet_monster";
        initFromFile(fileName);
        break;
    default :
        G_THROW("Unknown Case for Bullet");
    }

}

void Bullet::destructionAnim()
{
    //Get Position
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos *= World::ratio;

    //Create Effect
    Effect *e = new Effect(pos);
    e->getSprite().init("data/sprites/explo");

    //Add to the Manager
    EffectManager::instance()->add(e);
}
