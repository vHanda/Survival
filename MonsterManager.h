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
