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

#include "Page_2.h"

Page_2::Page_2()
{
    m_pImage = load_image("data/gfx/menu/page_2.png");
    m_pPlayer = load_image("data/gfx/player/player.png");
    m_Pos.x = 100;
    m_Pos.y = 400;
    m_State = state_right;
}

Page_2::~Page_2()
{
}

void Page_2::update(float timeElapsed)
{
    switch( m_State )
    {
    case state_left :
        m_Pos.x -= 7;
        break;
    case state_right :
        m_Pos.x += 7;
        break;
    }

    if( m_Pos.x < 200 )
        m_State = state_right;
    if( m_Pos.x > 600 )
        m_State = state_left;
}

void Page_2::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    SDL_BlitSurface( m_pPlayer.get(), NULL, screen, &m_Pos);
}

