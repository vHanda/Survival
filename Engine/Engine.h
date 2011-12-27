#ifndef _ENGINE_
#define _ENGINE_

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Keyboard.h"
#include "Mouse.h"
#include "ErrorHandler.h"

class Engine {
	SDL_Surface * m_pScreen;
	int m_iWidth, m_iHeight;

	std::string m_sCaption;

    //Boolean Variables
	bool m_bQuit;
	bool m_bMinimized;
	bool m_bFullScreen;

	//Input
	Keyboard * m_pKeyboard;
	Mouse * m_pMouse;

	//Frame Rate
	int tick;
	int last_tick;
	int m_iFps;
	int m_iMaxFps;

	void handle_events();
	void handle_framerate();
public :

	Engine();
	virtual ~Engine();

	void init(int width, int height);
	virtual void set_Icon() {}
	virtual void additional_init() = 0;
	virtual void render( SDL_Surface * screen ) = 0;
	virtual void calc(float timeElapsed) = 0;
	virtual void on_minimize() = 0;

	void run();
	void resize(int w, int h, Uint32 flags = 0);

	void set_caption(const std::string& c);
	const std::string& get_caption() const { return m_sCaption; }

	//FPS
	int get_fps() const { return m_iFps; }
    std::string get_fpss() const
    { std::stringstream ss; ss << m_iFps; return ss.str(); }

	//Keyboard and Mouse
	bool isKeyDown( const SDLKey & key ) const { return m_pKeyboard->isDown( key ); }
	bool isMouseDown( const int & b )	 const { return m_pMouse->isDown(b); }
	void getMousePos(int &x, int &y) 	 const { m_pMouse->getPos(x,y);}

	//Full Screen
	bool toggleFullScreen();

	void exit() { m_bQuit = true; }
	void quit() { exit(); }

	static const int bpp = 32;
};

#endif
