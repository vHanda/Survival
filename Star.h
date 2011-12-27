#ifndef STAR_H
#define STAR_H

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"
#include "Engine/Sprite.h"

class Star : public Box2DEntity
{
private :
    enum state {
        state_normal,
        state_invisible
    };

    state m_State;
    SDL_SurfacePtr m_pImage;
    float m_fLife;

    b2Vec2 m_StartPos;
    Sprite m_Sprite;
public:
    Star(b2World * pWorld, const b2Vec2 & startPos);
    virtual ~Star();

    void init();

    void update(float timeElapsed);
    void render();
    bool handleMessage(const Message & msg){return false;}

    bool done() { return m_fLife <= 0.0f; }
    std::string getType() { return "Star"; }

    void kill() { m_fLife = 0.0f; }

    void destructionAnim();
};

#endif // STAR_H
