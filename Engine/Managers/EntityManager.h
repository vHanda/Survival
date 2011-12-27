#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>

class Entity;

class EntityManager {
    std::map<int, Entity *> m_EntityMap;

public :
    EntityManager() {}
    ~EntityManager() {}
    static EntityManager * instance() { static EntityManager em; return &em; }

    void registerEntity(Entity * ent)
    { m_EntityMap.insert( std::make_pair( ent->getId(), ent ) ); }

    Entity * getEntity(int id)
    {
        if( m_EntityMap.find( id ) == m_EntityMap.end())
            return NULL;
        return m_EntityMap[id];
    }

    void removeEntity(Entity * ent)
    { m_EntityMap.erase( ent->getId() ); }
};

#define EntityMng EntityManager::instance()
#endif // ENTITYMANAGER_H_INCLUDED
