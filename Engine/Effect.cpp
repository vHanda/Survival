#include "Effect.h"
#include "../Camera.h"

Effect::Effect(const b2Vec2 & pos)
: m_vPos(pos)
{
    //ctor
}

Effect::~Effect()
{
    //dtor
}

void Effect::render()
{
    b2Vec2 pos = m_vPos;
    transform_Camera(pos);
    m_Sprite.render(pos);
}

void Effect::update(float timeElapsed)
{
    m_Sprite.update(timeElapsed);

}

