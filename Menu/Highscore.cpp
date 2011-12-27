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

#include "Highscore.h"
#include "../App.h"
#include <SDL/SDL_ttf.h>
#include <string>
#include "Menu.h"
#include "Help.h"
#include "../Score_func.h"
#include <sstream>
#include <iomanip>
HighScores::HighScores()
{

}

HighScores::~HighScores()
{

}

void HighScores::enter(App * a)
{
    m_pImage = load_image("data/gfx/menu/highscores.png");
    m_pLeftArrow = load_image("data/gfx/menu/left_arrow.png");

    std::vector<hScore> m_List;
    load_score(m_List);

    TTF_Font * pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF",35);
    SDL_Color black = {0,0,0,255};
    SDL_Rect rect;
    rect.x = 10;
    rect.y = 180;

    for(unsigned int i=0; i < m_List.size(); i++)
    {
        std::string str = createString(i, m_List[i]);
        SDL_SurfacePtr textImage = TTF_RenderText_Blended(pFont, str.c_str(), black);
        SDL_BlitSurface(textImage.get(), NULL, m_pImage.get(), &rect);

        rect.y += textImage->h + 10;
    }
    TTF_CloseFont(pFont);
}

void HighScores::update(App * a, float timeElapsed)
{
    //Same as credits
    if( a->isKeyDown( SDLK_ESCAPE ))
    {
        a->getFSM()->changeState(new Menu);
        return;
    }

    if( a->isMouseDown(1) )
    {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 600 - m_pLeftArrow->h;
        rect.w = m_pLeftArrow->w;
        rect.h = m_pLeftArrow->h;

        int x,y;
        a->getMousePos(x,y);
        b2Vec2 pos(x,y);

        if( ct_Rect_Point(rect, pos) )
        {
            a->getFSM()->changeState(new Menu);
            return;
        }
    }
}

void HighScores::render(App * a)
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface(m_pImage.get(), NULL, screen, NULL);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 600 - m_pLeftArrow->h;
    SDL_BlitSurface( m_pLeftArrow.get(), NULL, screen, &rect );
}

void HighScores::exit(App * a)
{
}

std::string HighScores::createString(int i, const hScore & h)
{
    std::stringstream ss;
    ss << i+1 << "  ";
    ss << std::left << std::setw(32) << h.name;
    ss << std::right << std::setw(4) << h.killed;
    ss << std::setw(15) << timeString(h.time);
    return ss.str();
}

std::string HighScores::timeString(int time)
{
    std::stringstream ss;
    int min = time / 60;
    if( min < 10 )
        ss << "0";
    ss << min << ":";

    int sec = time % 60;
    if(sec < 10)
        ss << "0";
    ss << sec;

    return ss.str();
}
