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
