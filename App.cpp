#include "App.h"
#include "Menu/AppStates.h"
#include "Game.h"
#include "Menu/Menu.h"
#include "Image/SDL_SurfacePtr.h"

App::App()
: m_Fsm(this)
{
}

App::~App()
{
    m_Fsm.clear();
}

void App::set_Icon()
{
    SDL_WM_SetIcon(IMG_Load("data/icon.png"), NULL);
}

void App::additional_init()
{
    m_Fsm.changeState(new Menu());

    //Cursor
    m_MouseSprite.init("data/sprites/mouse");
    m_MouseSprite.setPlayType(Sprite::play_loop);
    SDL_ShowCursor(0);

    //FPS
    m_pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF", 20);
    updateFps();

    //toggleFullScreen();
}

void App::render( SDL_Surface * screen )
{
    m_Fsm.render();

    int x,y;
    getMousePos(x,y);
    m_MouseSprite.render(b2Vec2(x,y));

    SDL_Rect rect;
    rect.x = 800 - m_pFpsImage->w;
    rect.y = 600 - m_pFpsImage->h;
    SDL_BlitSurface( m_pFpsImage.get(), NULL, screen, &rect );
}

void App::calc(float timeElapsed)
{
    static bool s = false;
    if(s == false)
    {
        srand( timeElapsed*1000 );
        s = true;
    }

    m_Fsm.update(timeElapsed);
    m_MouseSprite.update(timeElapsed);

    if(isKeyDown(SDLK_F1))
        toggleFullScreen();

    updateFps();
}

void App::on_minimize()
{

}

void App::updateFps()
{
    if(m_sFps != get_fpss())
    {
        m_sFps = get_fpss();
        SDL_Color c = {0,0,0,0};
        m_pFpsImage = TTF_RenderText_Solid(m_pFont, m_sFps.c_str(), c);
    }
}
