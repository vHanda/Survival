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

#include "Page_4.h"

Page_4::Page_4()
{
    m_pImage = load_image("data/gfx/menu/page_4.png");
    m_pPlayer = load_image("data/gfx/player/player.png");
    m_pShieldImage = load_image("data/gfx/shield/shield.png");

    m_Pos.x = 70;
    m_Pos.y = 300;
    m_State = state_right;
    m_fShieldDelay = 1.00;
}

Page_4::~Page_4()
{

}

void Page_4::update(float timeElapsed)
{
    switch( m_State )
    {
    case state_left :
        m_Pos.x -= 5;
        break;
    case state_right :
        m_Pos.x += 5;
        break;
    }

    if( m_Pos.x < 70 )
        m_State = state_right;
    if( m_Pos.x > 400 )
        m_State = state_left;

    //Add Shield
    if(m_fShieldDelay <= 0.0f)
    {
        Shield s;
        s.pos = m_Pos;
        s.vel.x = 6;
        s.vel.y = 6;

        if( rand() % 2 ) s.vel.x *= -1;
        if( rand() % 2 ) s.vel.y *= -1;

        m_List.push_back(s);
        m_fShieldDelay = 1.00;
    }

    //Adjuct Shield Pos
    for(unsigned int i=0; i<m_List.size(); i++)
    {
        m_List[i].pos.x += m_List[i].vel.x;
        m_List[i].pos.y += m_List[i].vel.y;

        if(m_List[i].pos.x <= 5 || m_List[i].pos.y <= 5)
        {
            m_List[i].pos.x = m_List[i].pos.y = 1000;
            m_List[i].vel = b2Vec2(0.0f, 0.0f);
        }
    }

    m_fShieldDelay -= timeElapsed;
}

void Page_4::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    SDL_BlitSurface( m_pPlayer.get(), NULL, screen, &m_Pos);
    for(unsigned int i=0; i<m_List.size(); i++)
    {
        SDL_BlitSurface( m_pShieldImage.get(), NULL, screen, &m_List[i].pos);
    }
}
