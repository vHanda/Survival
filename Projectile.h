#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"

class Agent;

class Projectile : public Box2DEntity
{
protected :
    SDL_SurfacePtr m_pImage;

    b2Vec2 m_StartPos;
    b2Vec2 m_Dir;

    float m_fSpeed;
    float m_fLife;
    float m_fDamage;

    Agent * m_pOwner;

    void initFromFile(const std::string & fileName);
public:
    Projectile(Agent * a, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Projectile();

    virtual void init();

    virtual void update(float timeElapsed);
    virtual void render();
    virtual bool handleMessage(const Message & msg) {return false;}

    //Life controlling
    virtual bool done() const { return m_fLife <= 0.0f; }
    virtual void kill() { m_fLife = 0.0f; }

    void resetOwner()   { m_pOwner = NULL; }

    float getDamage()   const { return m_fDamage; }
    Agent * getOwner()  const { return m_pOwner; }

    virtual void destructionAnim() = 0;
};

#endif // PROJECTILE_H
