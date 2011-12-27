#include "Entity.h"

int Entity::iNextValidId = 0;

Entity::Entity(int id)
{
    //ctor
    //std::cout << id << std::endl;
    m_pBody = NULL;
    if( id != -1 )
    {
        assert( id <= iNextValidId );
        m_iId = id;
        iNextValidId++;
    }
    else
    {
        m_iId = iNextValidId++;
        //std::cout << m_iId << std::endl;
    }
}

Entity::~Entity()
{
    //dtor
}
