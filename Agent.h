#ifndef AGENT_H
#define AGENT_H

#include "Box2DEntity.h"

class Map;
class Projectile;

class Agent : public Box2DEntity
{
protected :
    Map * m_pMap;

    SDL_SurfacePtr m_pImage;
    float m_fBulletTime;  //This is the time remaining untill another bullet may be fired.
    float m_fShieldTime;  //Same as above for Shields.
    float m_fBulletDelay;
    float m_fShieldDelay;
    float m_fSpeed;
    float m_fLife;
    float m_fMaxLife;

    void initFromXMLFile(std::string fileName, const b2Vec2 & startPos);
public:
    Agent(Map * pMap);
    virtual ~Agent() {deinit();}

    virtual void init() = 0;

    virtual void update(float timeElapsed)=0;
	virtual void render() =0;
    virtual bool handleMessage(const Message & msg) { return false; }

    Map * getMap() const { return m_pMap; }

    virtual bool isPlayer() const =0;

    //Life Functions
    bool done() const { return m_fLife <= 0.0f; }
    void reduceLife(float amt) { m_fLife -= amt; }

    float getLife() const { return m_fLife; }
    float getSpeed() const { return m_fSpeed; }

    virtual void handleProjectile(Projectile * proj);
    std::string getType() { return "Agent"; }

    float getPercentLife() const { return m_fLife/m_fMaxLife; }
};

#endif // AGENT_H
