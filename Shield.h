#ifndef SHIELD_H
#define SHIELD_H

#include "Projectile.h"

enum shield_type {
    shield_player =0,
    shield_monster
};

class Shield : public Projectile
{
private :
    shield_type m_Type;
public:
    Shield(Agent * a, shield_type st, const b2Vec2 & startPos, const b2Vec2 & dir);
    virtual ~Shield();

    virtual void init();

    std::string getType() { return "Shield"; }
    virtual void destructionAnim();
};

#endif // SHIELD_H
