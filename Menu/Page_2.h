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

#ifndef PAGE_2_H
#define PAGE_2_H

#include "Page.h"

class Page_2 : public Page
{
private :
    enum state {
        state_left,
        state_right
    };

    SDL_SurfacePtr m_pPlayer;
    SDL_Rect m_Pos;
    state m_State;
public:
    Page_2();
    virtual ~Page_2();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_2_H
