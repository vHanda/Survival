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

#ifndef APP_H
#define APP_H

#include "Engine/Engine.h"
#include "FSM/StateMachine.h"
#include "Engine/Sprite.h"
#include <SDL/SDL_ttf.h>

class App : public Engine
{
private:
    StateMachine<App> m_Fsm;
    Sprite m_MouseSprite;

    //FPS
    TTF_Font * m_pFont;
    std::string m_sFps;
    SDL_SurfacePtr m_pFpsImage;

    void updateFps();
public:
    App();
    virtual ~App();

    void set_Icon();
   	void additional_init();
	void render( SDL_Surface * screen );
	void calc(float timeElapsed);
	void on_minimize();

	StateMachine<App> * getFSM() { return &m_Fsm; }
};

#endif // APP_H
