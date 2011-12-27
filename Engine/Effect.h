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

#ifndef EFFECT_H
#define EFFECT_H

#include "Sprite.h"
#include "SoundEffect.h"

class Effect
{
protected :
    SoundEffect m_SoundEffect;
    Sprite m_Sprite;
    b2Vec2 m_vPos;
public:
    Effect(const b2Vec2 & pos = b2Vec2(0.00,0.00));
    virtual ~Effect();

    void addSound(Mix_Chunk * sound)
    { m_SoundEffect.assign(sound); }

    SoundEffect & getSoundEffect() { return m_SoundEffect; }
    Sprite & getSprite() { return m_Sprite; }

    virtual void render();
    virtual void update(float timeElapsed);

    Mix_Chunk * getSound() { return m_SoundEffect.getChunk(); }

    virtual bool done() { return soundDone() && animationDone(); }
    bool animationDone() { return m_Sprite.done(); }
    bool soundDone() { return m_SoundEffect.done(); }

    void setPos(const b2Vec2 & pos)
    { m_vPos = pos; }

    b2Vec2 getPos()
    { return m_vPos; }

};

#endif // EFFECT_H
