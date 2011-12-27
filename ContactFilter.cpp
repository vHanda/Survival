#include "ContactFilter.h"
#include "Agent.h"
#include "Bullet.h"
#include "Shield.h"

bool ContactFilter::ShouldCollide (b2Shape *shape1, b2Shape *shape2)
{
    void * userData1 = shape1->GetBody()->GetUserData();
    void * userData2 = shape2->GetBody()->GetUserData();

    if( userData1 == NULL || userData2 == NULL )
        return true;

    Entity * ent1 = (Entity*)userData1;
    Entity * ent2 = (Entity*)userData2;

    //For all permutations of Bullet, Shield and Agent.

    //Bullet and Bullet
    if( ent1->getType() == "Bullet" && ent2->getType() == "Bullet" )
    {
        Bullet * b1 = dynamic_cast<Bullet *>(ent1);
        Bullet * b2 = dynamic_cast<Bullet *>(ent2);

        if( b1->getOwner() == b2->getOwner() )
            return false;
    }

    //Bullet & Shield
    if( ent1->getType() == "Bullet" && ent2->getType() == "Shield" )
    {
        Bullet * b = dynamic_cast<Bullet *>(ent1);
        Shield * s = dynamic_cast<Shield *>(ent2);

        if( b->getOwner() == s->getOwner() )
            return false;
    }

    //Bullet & Agent
    if( ent1->getType() == "Bullet" && ent2->getType() == "Agent" )
    {
        Bullet * b = dynamic_cast<Bullet *>(ent1);
        Agent * a = dynamic_cast<Agent *>(ent2);

        if( b->getOwner() == a )
            return false;
    }

    //Shield  & Bullet
    if( ent1->getType() == "Shield" && ent2->getType() == "Bullet")
    {
        Bullet * b = dynamic_cast<Bullet *>(ent2);
        Shield * s = dynamic_cast<Shield *>(ent1);

        if( b->getOwner() == s->getOwner() )
            return false;
    }

    //Shield and Shield
    if( ent1->getType() == "Shield" && ent2->getType() == "Shield" )
    {
        Shield * s1 = dynamic_cast<Shield *>(ent1);
        Shield * s2 = dynamic_cast<Shield *>(ent2);

        if( s1->getOwner() == s2->getOwner() )
            return false;
    }

    //Shield and Agent
    //std::cout << "Trying Shield and Agent" << std::endl;
    if( ent1->getType() == "Shield" && ent2->getType() == "Agent" )
    {
        Shield * s = dynamic_cast<Shield *>(ent1);
        Agent * a = dynamic_cast<Agent *>(ent2);

        if( s->getOwner() == a )
            return false;
    }

    //Agent and Bullet
    if( ent1->getType() == "Agent" && ent2->getType() == "Bullet")
    {
        Bullet * b = dynamic_cast<Bullet *>(ent2);
        Agent * a = dynamic_cast<Agent *>(ent1);

        if( b->getOwner() == a )
            return false;
    }

    //Agent and Shield
    if( ent1->getType() == "Agent" && ent2->getType() == "Shield")
    {
        Shield * s = dynamic_cast<Shield *>(ent2);
        Agent * a = dynamic_cast<Agent *>(ent1);

        if( s->getOwner() == a )
            return false;
    }

    //Agent and Agent - returns true
    //All other cases
    return true;
}
