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

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

class Message;

template <typename T>
class State {
public :
    State() {}
    virtual ~State() {}

    virtual void enter(T * a) = 0;
    virtual void update(T * a, float timeElapsed) = 0;
    virtual void render(T * a) =0;
    virtual void exit(T * a) = 0;
    virtual bool handleMessage(T * a, const Message & m) = 0;
};

#endif // STATE_H_INCLUDED
