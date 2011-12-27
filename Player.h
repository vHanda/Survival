#ifndef PLAYER_H
#define PLAYER_H

#include "Agent.h"
#include "Image/SDL_SurfacePtr.h"
#include "Engine/Sprite.h"

class Map;

class Player : public Agent
{
private:
    Sprite m_Sprite;
    void fireBullet();
    void fireShield();

    int m_iMonstersKilled;
public:
    Player(Map * map);
    virtual ~Player();

    void init();

    void update(float timeElapsed);
	void render();
    bool handleMessage(const Message & msg);

    bool isPlayer() const { return true; }
    void addStar() {m_fLife += 1.0f;}

    int killed() const { return m_iMonstersKilled; }

    void monsterKilled() { m_iMonstersKilled += 1; }
};

#endif // PLAYER_H
