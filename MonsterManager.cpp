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

