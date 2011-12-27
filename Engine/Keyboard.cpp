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

