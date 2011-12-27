#ifndef BULLET_H
#define BULLET_H

#include "Projectile.h"

enum bullet_type {
    bullet_player =0,
    bullet_monster=1
};

class Bullet : public Projectile
{
private :
    bullet_type m_Type;
public:
    Bullet(Agent * a, bullet_type bt, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Bullet();

    virtual void init();

    std::string getType() { return "Bullet"; }
    virtual void destructionAnim();
};

#endif // BULLET_H
