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
