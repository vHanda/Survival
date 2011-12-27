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

#ifndef PAGE_4_H
#define PAGE_4_H

#include "Page.h"
#include <vector>
#include <Box2D/Box2D.h>

class Page_4 : public Page
{
private :
    enum state {
        state_left,
        state_right
    };

    SDL_SurfacePtr m_pPlayer;
    SDL_SurfacePtr m_pShieldImage;
    SDL_Rect m_Pos;
    state m_State;

    struct Shield {
        SDL_Rect pos;
        b2Vec2 vel;
    };

    std::vector<Shield> m_List;
    float m_fShieldDelay;
public:
    Page_4();
    virtual ~Page_4();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_4_H
