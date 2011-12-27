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

#ifndef MESSAGE_H
#define MESSAGE_H
#include <SDL/SDL.h>

class Message {
private :
    static int iLeastDiff;
public :
    int from, to;
    int message;
    float timeDelay;
    void * data;
    int timeSent;

    Message(int f, int t, int m, float tD = 0.0f, void * d=0)
    : from(f), to(t), message(m), timeDelay(tD), data(d)
    { timeSent= SDL_GetTicks() + iLeastDiff++;}

    virtual ~Message() {}

    bool operator <(const Message & rhs) const
    {
        if(timeDelay == rhs.timeDelay)
        {
            if(timeSent == rhs.timeSent)
                assert( !"Damn Messages not unique" );
            return timeSent < rhs.timeSent;
        }
        return timeDelay < rhs.timeDelay;
    }
    bool operator ==(const Message & rhs) const
    {
        return from == rhs.from && to==rhs.to && message == rhs.message &&
                timeDelay == rhs.timeDelay && timeSent==rhs.timeSent;
    }
};

#endif
