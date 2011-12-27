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
