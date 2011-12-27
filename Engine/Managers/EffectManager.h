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

#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "../Effect.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <map>
#include <SDL/SDL_mixer.h>

class EffectManager
{
private:
    EffectManager();
    virtual ~EffectManager();

    boost::ptr_list<Effect> m_List;
public :
    static EffectManager * instance() { static EffectManager em; return &em; }

    void add(Effect * effect)
    { m_List.push_back(effect); effect->getSoundEffect().play();}

	void add(Mix_Chunk * chunk)
	{ Effect * e = new Effect(); e->addSound(chunk); add(e); }

    void remove(Effect * effect)
    {assert(!"Not Implemented - Removal of Effects");}

    void update(float timeElapsed);
    void render();

    void clear()
    { m_List.clear(); Mix_HaltChannel(-1);}

    void pause()
    { Mix_Pause(-1); }

    void resume()
    { Mix_Resume(-1); }
};

#endif // EFFECT_MANAGER_H
