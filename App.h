#ifndef APP_H
#define APP_H

#include "Engine/Engine.h"
#include "FSM/StateMachine.h"
#include "Engine/Sprite.h"
#include <SDL/SDL_ttf.h>

class App : public Engine
{
private:
    StateMachine<App> m_Fsm;
    Sprite m_MouseSprite;

    //FPS
    TTF_Font * m_pFont;
    std::string m_sFps;
    SDL_SurfacePtr m_pFpsImage;

    void updateFps();
public:
    App();
    virtual ~App();

    void set_Icon();
   	void additional_init();
	void render( SDL_Surface * screen );
	void calc(float timeElapsed);
	void on_minimize();

	StateMachine<App> * getFSM() { return &m_Fsm; }
};

#endif // APP_H
