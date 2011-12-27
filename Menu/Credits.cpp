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

#include "Credits.h"
#include <string>
#include "Menu.h"
#include "Help.h"

Credits::Credits()
{
}

Credits::~Credits()
{
}

void Credits::enter(App * a)
{
    m_pImage = SDL_CreateRGBSurface(800, 600);
    SDL_FillRect( m_pImage.get(), NULL, 0xFFFFFFFF );

    TTF_Font * pFont = TTF_OpenFont("data/fonts/Ayuma2yk.ttf", 55);
    SDL_Color blackColor = {0,0,0,0};

    std::string text = "Programming, Art and Game Design";
    SDL_SurfacePtr pTextImage = TTF_RenderText_Blended(pFont, text.c_str(), blackColor);

    SDL_Rect rect;
    rect.x = 800/2 - pTextImage->w/2;
    rect.y = 200;
    SDL_BlitSurface(pTextImage.get(), NULL, m_pImage.get(), &rect);
    rect.y += pTextImage->h;

    text = "by Vishesh Handa";
    SDL_SurfacePtr pTextImage2 = TTF_RenderText_Blended(pFont, text.c_str(), blackColor);
    rect.x = 800/2 - pTextImage2->w/2;
    SDL_BlitSurface(pTextImage2.get(), NULL, m_pImage.get(), &rect);

    TTF_CloseFont(pFont);

    m_pLeftArrow = load_image("data/gfx/menu/left_arrow.png");
}

void Credits::update(App * a, float timeElapsed)
{
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

void Credits::render(App * a)
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface(m_pImage.get(), NULL, screen, NULL);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 600 - m_pLeftArrow->h;
    SDL_BlitSurface( m_pLeftArrow.get(), NULL, screen, &rect );
}

void Credits::exit(App * a)
{
}

