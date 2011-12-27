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

#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "FSM/State.h"
#include "Game.h"
#include "Engine/Effect.h"
#include "TextBox.h"

class Game_Init : public State<Game> {
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Play : public State<Game> {
private :
    Mix_Music * m_pMusic;
    SDL_SurfacePtr m_pPausedImage;

    enum state {
        state_run,
        state_pause
    };

    state m_State;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Death : public State<Game> {
private :
    Sprite m_Sprite;
    SoundEffect m_SoundEffect;
    b2Vec2 m_Pos;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Highscore : public State<Game> {
private :
    SDL_SurfacePtr m_pImage;
    SDL_Rect m_Rect;
    TextBox m_TextBox;

    void addToHighscores(Game * g) const;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

#endif // GAMESTATES_H
