#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class Bullet;
class Shield;
class Agent;
class Star;

class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    virtual ~ContactListener();

    void Add(const b2ContactPoint *point);
    void Persist(const b2ContactPoint *point){}
    void Remove(const b2ContactPoint *point){}
    void Result(const b2ContactResult *point){}
protected:
private:
};

void handle_Bullet_Bullet(Bullet * b1, Bullet * b2);
void handle_Bullet_Shield(Bullet * b, Shield * s);
void handle_Agent_Bullet(Agent * a, Bullet * b);
void handle_Agent_Agent(Agent * a1, Agent * a2, const b2Vec2 & pos);
void handle_Agent_Star(Agent * a, Star *s);
void handle_Agent_Shield(Agent * a, Shield * s);
void handle_Bullet_Obstacle(Bullet *b);
void handel_Shield_Shield(Shield * s1, Shield * s2);


#endif // CONTACTLISTENER_H
