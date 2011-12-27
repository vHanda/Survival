#include "Page_1.h"

Page_1::Page_1()
{
    m_pImage = load_image("data/gfx/menu/page_1.png");
}

Page_1::~Page_1()
{

}

void Page_1::update(float timeElapsed)
{
}

void Page_1::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );
}
