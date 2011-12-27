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

#include "Keyboard.h"
#include <iostream>

bool Keyboard::keys[512];
char Keyboard::keychar[512];
SDLMod Keyboard::modifier;

Keyboard::Keyboard()
{
	for( int i = 0; i < 128; i++ )
	{
		keys[i] = 0;
		keychar[i] = ' ';
	}
}

void Keyboard::onKeyDown( const SDLKey & key, const SDLMod & mod, char ch)
{
	keys[key]++;
	modifier = mod;
    keychar[key] = ch;
    //std::cout << "Pressed - " << SDL_GetKeyName(key) << std::endl;

}

void Keyboard::onKeyUp(  const SDLKey & key, const SDLMod & mod, char ch)
{
	keys[key] = 0;
	modifier = mod;
    keychar[key] = ch;

    //std::cout << "Released - " << SDL_GetKeyName(key) << std::endl;
}

