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

#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include "Engine/Managers/EffectManager.h"
#include "GameStates.h"
#include "Menu/Highscore.h"
#include "Menu/Menu.h"

Game::Game()
: m_Fsm(this)
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::enter(App * a)
{
    //Init World
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-300.0f, -300.0f);
    worldAABB.upperBound.Set(300.0f, 300.0f);
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;

    m_pWorld = std::auto_ptr<b2World>(new b2World(worldAABB, gravity, doSleep));

    //Init Map
    m_pMap = std::auto_ptr<Map>(new Map(m_pWorld.get()));
    m_pMap->init();

    m_pPlayer = std::auto_ptr<Player>(new Player(m_pMap.get()));
    m_pPlayer->init();

    m_pMonsterM = std::auto_ptr<MonsterManager>(new MonsterManager( m_pMap.get(), m_pPlayer.get() ));
    m_pMonsterM->init();

    m_pWorld->SetContactListener( &m_ContactListener );
    m_pWorld->SetContactFilter( &m_ContactFilter );
    m_pWorld->SetDebugDraw( &m_DebugDraw );
    Camera::getInstance()->set(m_pPlayer.get());

    m_Fsm.changeState( new Game_Init() );
    m_bDone = false;

    //Timer
    m_Timer.init();
    m_Timer.setPos(0);
    m_Score.init();
    m_Score.setPos(25);
}

void Game::update(App * a, float timeElapsed)
{
    if( m_bDone == true )
    {
        a->getFSM()->changeState(new HighScores);
        return;
    }

    //State
    m_Fsm.update(timeElapsed);

    m_Timer.update(timeElapsed);
    m_Score.update( m_pMonsterM->killed() );

    if( a->isKeyDown( SDLK_ESCAPE ) )
    {
        a->getFSM()->changeState(new Menu);
        return;
    }
}

void Game::render(App * a)
{
    m_Fsm.render();
    m_Timer.render();
    m_Score.render();
}

void Game::exit(App * a)
{
    m_Fsm.clear();
    //TODO Reset the auto Pointers if added
    m_pMonsterM->deinit();
    m_pPlayer->deinit();
    m_pMap->deinit();

    m_pMap.reset();
    m_pPlayer.reset();
    m_pMonsterM.reset();
    m_pWorld.reset();

    EffectManager::instance()->clear();
}

void Game::done()
{
    m_bDone = true;
}
