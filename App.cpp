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

#include "App.h"
#include "Menu/AppStates.h"
#include "Game.h"
#include "Menu/Menu.h"
#include "Image/SDL_SurfacePtr.h"

App::App()
: m_Fsm(this)
{
}

App::~App()
{
    m_Fsm.clear();
}

void App::set_Icon()
{
    SDL_WM_SetIcon(IMG_Load("data/icon.png"), NULL);
}

void App::additional_init()
{
    m_Fsm.changeState(new Menu());

    //Cursor
    m_MouseSprite.init("data/sprites/mouse");
    m_MouseSprite.setPlayType(Sprite::play_loop);
    SDL_ShowCursor(0);

    //FPS
    m_pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF", 20);
    updateFps();

    //toggleFullScreen();
}

void App::render( SDL_Surface * screen )
{
    m_Fsm.render();

    int x,y;
    getMousePos(x,y);
    m_MouseSprite.render(b2Vec2(x,y));

    SDL_Rect rect;
    rect.x = 800 - m_pFpsImage->w;
    rect.y = 600 - m_pFpsImage->h;
    SDL_BlitSurface( m_pFpsImage.get(), NULL, screen, &rect );
}

void App::calc(float timeElapsed)
{
    static bool s = false;
    if(s == false)
    {
        srand( timeElapsed*1000 );
        s = true;
    }

    m_Fsm.update(timeElapsed);
    m_MouseSprite.update(timeElapsed);

    if(isKeyDown(SDLK_F1))
        toggleFullScreen();

    updateFps();
}

void App::on_minimize()
{

}

void App::updateFps()
{
    if(m_sFps != get_fpss())
    {
        m_sFps = get_fpss();
        SDL_Color c = {0,0,0,0};
        m_pFpsImage = TTF_RenderText_Solid(m_pFont, m_sFps.c_str(), c);
    }
}
