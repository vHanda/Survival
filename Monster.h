#ifndef MONSTER_H
#define MONSTER_H

#include "Agent.h"
#include "Image/SDL_SurfacePtr.h"
#include "Neural_SB.h"
#include <memory>

class Player;

class Monster : public Agent
{
private:
    Player * m_pPlayer;
    std::auto_ptr<Neural_SB> m_pSB;
    NN_File * m_pBrain;

    //Internal Firing
    bool fireBullet(const b2Vec2 & dir);
    bool fireShield(const b2Vec2 & dir);

    static const float MinDistance = 20.0f;

public:
    Monster(Map * map, Player * player, NN_File * pBrain);
    virtual ~Monster();

    void init();
    void deinit();

    void update(float timeElapsed);
	void render();
    bool handleMessage(const Message & msg);

    bool isPlayer() const { return false; }

    bool canFireBullet() const { return m_fBulletTime <= 0.0f; }
    bool canFireShield() const { return m_fShieldTime <= 0.0f; }

    void fireBullet();
    void fireShield();

    Player * getPlayer() const { return m_pPlayer; }

    void destructionAnim();
    void addStar() const;
};

#endif // MONSTER_H
