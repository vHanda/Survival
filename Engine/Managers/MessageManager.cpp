#include "MessageManager.h"
#include "../Entity.h"
#include "EntityManager.h"
#include "../Message.h"

int Message::iLeastDiff = 1;

MessageManager::MessageManager()
{
    //ctor
}

MessageManager::~MessageManager()
{
    //dtor
}

void MessageManager::add(const Message & m)
{
    m_PQ.insert( m );
    //std::cout << "Size : " << m_PQ.size() << std::endl;
}

void MessageManager::update(float timeElapsed)
{
    typedef std::set<Message>::iterator PQ_Iter;
    PQ_Iter it = m_PQ.begin();
    while( it != m_PQ.end() )
    {
        if(it->timeDelay > 0.0f)
            break;
        Entity * rec = EntityManager::instance()->getEntity( it->to );
        if(rec != NULL)
        {
            rec->handleMessage( *it );
        }
        else
        {
            std::cout << "!Messge needs to be sent to " <<  it->to << std::endl;
            assert(!"Message Manager - Id->Entity Not found");
        }
        it++;
    }

    m_PQ.erase( m_PQ.begin(), it );

    PQ_Iter iter = m_PQ.begin();
    while( iter != m_PQ.end() )
    {
        //WHY IS IT RETURNING A CONST !!!
        const Message * cm = &(*iter);
        Message * m = const_cast<Message *>(cm);
        m->timeDelay -= timeElapsed;
        iter++;
    }
}
