#include "Page_2.h"

Page_2::Page_2()
{
    m_pImage = load_image("data/gfx/menu/page_2.png");
    m_pPlayer = load_image("data/gfx/player/player.png");
    m_Pos.x = 100;
    m_Pos.y = 400;
    m_State = state_right;
}

Page_2::~Page_2()
{
}

void Page_2::update(float timeElapsed)
{
    switch( m_State )
    {
    case state_left :
        m_Pos.x -= 7;
        break;
    case state_right :
        m_Pos.x += 7;
        break;
    }

    if( m_Pos.x < 200 )
        m_State = state_right;
    if( m_Pos.x > 600 )
        m_State = state_left;
}

void Page_2::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    SDL_BlitSurface( m_pPlayer.get(), NULL, screen, &m_Pos);
}

