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

#include "TextBox.h"
#include <ctime>
#include <iostream>

TextBox::TextBox()
{
    //ctor
    m_pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF", 50);

    m_Pos.x = 0;
    m_Pos.y = 0;

    m_iTimes = 0;
    m_bDone = false;

    SDL_EnableUNICODE( 1 );
    //SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

TextBox::~TextBox()
{
    //dtor
    if(m_pFont)
        TTF_CloseFont(m_pFont);

    SDL_EnableUNICODE( 0 );
    //SDL_EnableKeyRepeat( 0, 0 );
}

void TextBox::update(float timeElapsed)
{
    if(m_bDone == true)
        return;

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;

    m_pTextImage = TTF_RenderText_Blended(m_pFont, m_sText.c_str(), color);

    Keyboard * kb = Keyboard::getInstance();
    SDLKey key = kb->isKeyDown();
    int times = kb->isDown(key);

    //std::cout << key << "\t" << m_LastKey << "\t" << times << "\t" << m_iTimes;

    if( m_LastKey != key)
    {
        //std::cout << " - True"<< std::endl;
        m_LastKey = key;
        m_iTimes = times;

        if(key == SDLK_RETURN)
        {
            m_bDone = true;
            return;
        }
        if(key == SDLK_BACKSPACE && m_sText.empty() == false)
        {
            m_sText.erase( m_sText.end() -1);
            return;
        }
        if(m_sText.length() >= 16)
            return;

        char ch = kb->getChar( key );
        if( SDLK_a <= key && key <= SDLK_z)
            m_sText += ch;
        if( SDLK_0 <= key && key <= SDLK_9)
            m_sText += ch;
        if( key == SDLK_SPACE )
            m_sText += ' ';

    }
    else if( m_iTimes < times )
    {
        //std::cout << m_iTimes << "\t" << times << std::endl;
        m_iTimes++;
        char ch = kb->getChar( key );
        m_sText += ch;
    }
    //else
    //    std::cout << "\n";

}

void TextBox::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();

    SDL_Rect rect = m_Pos;
    SDL_BlitSurface( m_pTextImage.get(), NULL, screen, &rect);
}
