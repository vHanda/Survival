#ifndef EFFECT_H
#define EFFECT_H

#include "Sprite.h"
#include "SoundEffect.h"

class Effect
{
protected :
    SoundEffect m_SoundEffect;
    Sprite m_Sprite;
    b2Vec2 m_vPos;
public:
    Effect(const b2Vec2 & pos = b2Vec2(0.00,0.00));
    virtual ~Effect();

    void addSound(Mix_Chunk * sound)
    { m_SoundEffect.assign(sound); }

    SoundEffect & getSoundEffect() { return m_SoundEffect; }
    Sprite & getSprite() { return m_Sprite; }

    virtual void render();
    virtual void update(float timeElapsed);

    Mix_Chunk * getSound() { return m_SoundEffect.getChunk(); }

    virtual bool done() { return soundDone() && animationDone(); }
    bool animationDone() { return m_Sprite.done(); }
    bool soundDone() { return m_SoundEffect.done(); }

    void setPos(const b2Vec2 & pos)
    { m_vPos = pos; }

    b2Vec2 getPos()
    { return m_vPos; }

};

#endif // EFFECT_H
