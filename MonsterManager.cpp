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

#include "MonsterManager.h"
#include "Monster.h"
#include "Map.h"
#include "Player.h"
#include <algorithm>
#include <boost/bind.hpp>
#include "ContactListener.h"
#include "Star.h"

MonsterManager::MonsterManager(Map * pMap, Player * pPlayer)
: m_pMap(pMap), m_pPlayer(pPlayer)
{
}

void MonsterManager::init()
{
    m_iMonstersKilled = 0;

    m_pMonsterBrain = std::auto_ptr<NN_File>(new NN_File());
    //m_pMonsterBrain->train("data/training_set");
    //m_pMonsterBrain->saveToFile("data/newBrain");
    m_pMonsterBrain->loadFromFile("data/newBrain");
}

void MonsterManager::deinit()
{
    m_pMonsterBrain.reset();
    m_Monsters.clear();
}

void MonsterManager::update(float timeElapsed)
{
    std::for_each(  m_Monsters.begin(), m_Monsters.end(),
                    boost::bind(&Monster::update, _1, timeElapsed) );

    //Add star and effect
    boost::ptr_list<Monster>::iterator it = m_Monsters.begin();
    while(it != m_Monsters.end())
    {
        if(it->done() == true)
        {
            m_iMonstersKilled++;
            m_pPlayer->monsterKilled();
            it->destructionAnim();
            it->addStar();
        }
        it++;
    }

    m_Monsters.erase_if( std::mem_fun_ref(& Monster::done ) );

    regenerateMonsters();
}

void MonsterManager::render()
{
    std::for_each( m_Monsters.begin(), m_Monsters.end(), std::mem_fun_ref(&Monster::render) );
}

void MonsterManager::regenerateMonsters()
{
    //Increase the num of monsters if some have died
    unsigned int num = 0;
    if( m_iMonstersKilled > 1 )
        num = MaxMonsters * (m_iMonstersKilled/100.0);
    if( num < 3 ) num = 3;
    if( num > MaxMonsters ) num = MaxMonsters;

    while( m_Monsters.size() < num )
    {
        Monster * m = new Monster(m_pMap, m_pPlayer, m_pMonsterBrain.get());
        m->init();
        m_Monsters.push_back(m);
    }
}

