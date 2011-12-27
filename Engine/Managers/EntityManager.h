/*
 * Survival
 *
 * Copyright (C) 2009-2011 Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
