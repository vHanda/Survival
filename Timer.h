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

#ifndef TIMER_H
#define TIMER_H

#include "Image/SDL_SurfacePtr.h"
#include <SDL/SDL_ttf.h>

class Timer
{
private :
    enum State {
        state_run,
        state_pause
    };

    State m_State;
    float m_fSecTime;
    int m_iTotalTime;
    TTF_Font * m_pFont;
    SDL_SurfacePtr m_pImage;
    SDL_Rect m_Rect;

    void renderTime();

public:
    Timer();
    virtual ~Timer();

    void init();
    void deinit();

    void update(float timeElapsed);
    void render();

    void setPos(int y)
    { m_Rect.y = y; }

    void pause() { m_State = state_pause; }
    void run() { m_State = state_run; }

    int time() { return m_iTotalTime; }
    std::string get() const;
};

#endif // TIMER_H
