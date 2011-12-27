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

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include <SDL/SDL.h>
#include <cassert>
#include <vector>

class Keyboard {
private :
	static bool keys[512];
	static char keychar[512];
	static SDLMod modifier;
public :
	Keyboard();
	~Keyboard() {}
	void onKeyDown( const SDLKey & key, const SDLMod & mod, char ch);
	void onKeyUp( const SDLKey & key, const SDLMod & mod, char ch);

	int isDown(const SDLKey & key) const
	{ assert( key < 512 && "Keyboard Error !!"); return keys[key]; }

	static Keyboard * getInstance() { static Keyboard k; return &k; }

    SDLKey isKeyDown()
    {
        for(int i=0;i<512;i++)
            if(keys[i])
                return (SDLKey)i;
        return (SDLKey)0;
    }

    char getChar(const SDLKey & key)
    {
        return keychar[key];
    }
};

#define gKB Keyboard::getInstance()


#endif
