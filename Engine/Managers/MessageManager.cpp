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
