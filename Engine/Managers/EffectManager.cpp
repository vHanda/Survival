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

#include "EffectManager.h"

EffectManager::EffectManager()
{
    //ctor

}

EffectManager::~EffectManager()
{
    //dtor
}

void EffectManager::render()
{
    typedef boost::ptr_list<Effect>::iterator ELI;
    for(ELI i = m_List.begin(); i!=m_List.end(); i++)
        i->render();
}

void EffectManager::update(float timeElapsed)
{
    //Cleanup
    m_List.erase_if( std::mem_fun_ref(&Effect::done) );

    typedef boost::ptr_list<Effect>::iterator ELI;
    for(ELI i = m_List.begin(); i!=m_List.end(); i++)
        i->update(timeElapsed);
}
