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

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>

class App;
class hScore;

class HighScores : public State<App>
{
    SDL_SurfacePtr m_pImage;
    SDL_SurfacePtr m_pLeftArrow;

    std::string createString(int i, const hScore & h);
    std::string timeString(int time);
public :
    HighScores();
    ~HighScores();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};


#endif // HIGHSCORE_H
