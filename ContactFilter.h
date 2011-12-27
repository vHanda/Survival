#ifndef CONTACTFILTER_H
#define CONTACTFILTER_H

#include "Box2D/Box2D.h"

class ContactFilter : public b2ContactFilter
{
public:
    virtual bool ShouldCollide (b2Shape *shape1, b2Shape *shape2);
};

#endif // CONTACTFILTER_H
