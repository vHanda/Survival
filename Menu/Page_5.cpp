#include "Page_5.h"

Page_5::Page_5()
{
    m_pImage = load_image("data/gfx/menu/page_5.png");
    m_Sprite.init("data/sprites/player_sprite");
    m_Sprite.setFPS( 3 );
    m_Sprite.setPlayType( Sprite::play_loop );
}

Page_5::~Page_5()
{
}

void Page_5::update(float timeElapsed)
{
    m_Sprite.update(timeElapsed);
}

void Page_5::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    m_Sprite.render( b2Vec2( 210, 275 ) );
}
