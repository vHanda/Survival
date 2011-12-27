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

#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include <boost/ptr_container/ptr_list.hpp>
#include "Monster.h"
#include "NeuralNetwork/NN_File.h"

class Map;
class Player;


class MonsterManager
{
private :
    Map * m_pMap;
    Player * m_pPlayer;
    std::auto_ptr<NN_File> m_pMonsterBrain;
    boost::ptr_list<Monster> m_Monsters;
    int m_iMonstersKilled;

    static const int MaxMonsters = 50;

    void regenerateMonsters();
public:
    MonsterManager(Map * pMap, Player * pPlayer);
    virtual ~MonsterManager() {deinit();}

    void init();
    void deinit();

    void update(float timeElapsed);
    void render();

    int killed() const { return m_iMonstersKilled; }
};

#endif // MONSTERMANAGER_H
