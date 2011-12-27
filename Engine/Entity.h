#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <string>

class Message;

class Entity
{
public:
    Entity(int id = -1);
    virtual ~Entity();

    b2Body * getBody() const { return m_pBody; }
    int getId() const { return m_iId; }

    virtual void update(float timeElapsed)=0;
	virtual void render() =0;
    virtual bool handleMessage(const Message & msg) = 0;
    static void reset() { iNextValidId = 0; }

    virtual std::string getType() = 0;
protected :
    b2Body* m_pBody;
private :
    int m_iId;
	static int iNextValidId;
};

#endif // ENTITY_H
