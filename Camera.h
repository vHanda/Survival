#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>
#include <cassert>
#include "Engine/Mouse.h"
#include "World.h"

class Player;

class Camera
{
private:
    enum State {
        state_Normal,
        state_Vibrational
    };

    State m_State;
    SDL_Rect m_Rect;
    b2Vec2 m_Vel;
    Player * m_pPlayer;

    float m_fPlayerLife;
    float m_fVibrationTime;
    float m_fMaxVelocity;

    static const float VibrationTime = 0.25f;

    Camera();
    virtual ~Camera();
    void constructRect(b2Vec2 pos);
public:
    void set(Player * ent);

    static Camera * getInstance()
    {
        static Camera c;
        return &c;
    }

    const SDL_Rect & getRect() const { return m_Rect; }
    void update(float timeElapsed);
};

void transform_Camera(SDL_Rect & rect);
void transform_Camera(b2Vec2 & vec);

inline b2Vec2 getCursorWorldCoords()
{
    //Get Screen Coords
    int x,y;
    Mouse::getInstance()->getPos(x,y);
    //Convert to world pixel coords
    x += Camera::getInstance()->getRect().x;
    y += Camera::getInstance()->getRect().y;

    //Convert to world physics engine coords and save in dir.
    b2Vec2 pos;
    pos.x = x / (float)World::ratio;
    pos.y = y / (float)World::ratio;

    return pos;
}
#endif // CAMERA_H
