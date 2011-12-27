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

#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <set>
class Message;

class MessageManager
{
private :
    std::set<Message> m_PQ;

    MessageManager();
    ~MessageManager();

public :
    void add(const Message & m);
    void update(float timeElapsed);

    static MessageManager * instance()
    {
        static MessageManager mm;
        return &mm;
    }
};

#endif // MESSAGEMANAGER_H
