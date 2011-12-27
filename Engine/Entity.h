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
