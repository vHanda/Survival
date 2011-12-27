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

#include "Score.h"
#include <string>
#include <sstream>

ScoreBoard::ScoreBoard()
{
    //ctor
}

ScoreBoard::~ScoreBoard()
{
    //dtor
    deinit();
}

void ScoreBoard::init()
{
    m_iKilled = 0;
    m_pFont = TTF_OpenFont("data/fonts/BEARPAW_.TTF", 50);

    m_Rect.x = 0;
    m_Rect.y = 0;


    renderScore();
}

void ScoreBoard::deinit()
{
    if(m_pFont != NULL)
    {
        TTF_CloseFont(m_pFont);
        m_pFont = NULL;
    }
}

void ScoreBoard::update(int kills)
{
    if( kills != m_iKilled )
    {
        m_iKilled = kills;
        renderScore();
    }
}
void ScoreBoard::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, &m_Rect);
}

void ScoreBoard::renderScore()
{
    std::stringstream ss;
    ss << "Kills : " << m_iKilled;
    const char * str = ss.str().c_str();

    SDL_Color black = {0,0,0,255};
    m_pImage = TTF_RenderText_Blended( m_pFont, str, black );

    m_Rect.x = 800 - m_pImage->w;
}
