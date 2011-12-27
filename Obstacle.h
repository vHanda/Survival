#ifndef OBSTACLE_INCLUDED
#define OBSTACLE_INCLUDED

#include "Box2DEntity.h"
#include "Image/SDL_SurfacePtr.h"

class Obstacle : public Box2DEntity {
private :
    SDL_SurfacePtr m_pImage;
    b2Vec2 m_StartPos;
public :
    Obstacle(b2World * pWorld, const b2Vec2 & startPos)
    : Box2DEntity(pWorld), m_StartPos(startPos) {}
    ~Obstacle() { deinit(); }

    void init();
    void deinit();

    void update(float timeElapsed);
    void render();

    std::string getType() { return "Obstacle"; }
    bool handleMessage(const Message & msg)
    { return false; }
};

#endif // OBSTACLE_INCLUDED
