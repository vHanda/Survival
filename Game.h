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

#ifndef GAME_H
#define GAME_H

#include "App.h"
#include <memory>
#include "Map.h"
#include "Player.h"
#include "DebugDraw.h"
#include "ContactListener.h"
#include "ContactFilter.h"
#include "MonsterManager.h"
#include "Engine/Sprite.h"
#include "FSM/StateMachine.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Timer.h"
#include "Score.h"
#include <memory>

class Game : public State<App>
{
private:
    std::auto_ptr<b2World>      m_pWorld;
    std::auto_ptr<Map>          m_pMap;
    std::auto_ptr<Player>       m_pPlayer;
    std::auto_ptr<MonsterManager> m_pMonsterM;

    //Clock and Score
    Timer m_Timer;
    ScoreBoard m_Score;

    //Box2D
    DebugDraw m_DebugDraw;
    ContactListener m_ContactListener;
    ContactFilter m_ContactFilter;

    StateMachine<Game> m_Fsm;

    bool m_bDone;
    //Score
public:
    Game();
    virtual ~Game();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
    void exit(App * a);

    Map * getMap()                  const { return m_pMap.get(); }
    Player * getPlayer()            const { return m_pPlayer.get(); }
    MonsterManager * getMonsters()  const { return m_pMonsterM.get(); }
    b2World * getWorld()            const { return m_pWorld.get(); }
    StateMachine<Game> * getFsm()   { return &m_Fsm; }

    void done();
    Timer * getTimer() { return &m_Timer; }
    int getScore() { return m_pMonsterM->killed(); }
};

#endif // GAME_H
