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

#ifndef PLAYER_H
#define PLAYER_H

#include "Agent.h"
#include "Image/SDL_SurfacePtr.h"
#include "Engine/Sprite.h"

class Map;

class Player : public Agent
{
private:
    Sprite m_Sprite;
    void fireBullet();
    void fireShield();

    int m_iMonstersKilled;
public:
    Player(Map * map);
    virtual ~Player();

    void init();

    void update(float timeElapsed);
	void render();
    bool handleMessage(const Message & msg);

    bool isPlayer() const { return true; }
    void addStar() {m_fLife += 1.0f;}

    int killed() const { return m_iMonstersKilled; }

    void monsterKilled() { m_iMonstersKilled += 1; }
};

#endif // PLAYER_H
