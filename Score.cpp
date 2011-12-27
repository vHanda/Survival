#include "Score.h"
#include <string>
#include <sstream>

ScoreBoard::ScoreBoard()
{
    //ctor
}

ScoreBoard::~ScoreBoard()
{
    //dtor
    deinit();
}

void ScoreBoard::init()
{
    m_iKilled = 0;
    m_pFont = TTF_OpenFont("data/fonts/BEARPAW_.TTF", 50);

    m_Rect.x = 0;
    m_Rect.y = 0;


    renderScore();
}

void ScoreBoard::deinit()
{
    if(m_pFont != NULL)
    {
        TTF_CloseFont(m_pFont);
        m_pFont = NULL;
    }
}

void ScoreBoard::update(int kills)
{
    if( kills != m_iKilled )
    {
        m_iKilled = kills;
        renderScore();
    }
}
void ScoreBoard::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, &m_Rect);
}

void ScoreBoard::renderScore()
{
    std::stringstream ss;
    ss << "Kills : " << m_iKilled;
    const char * str = ss.str().c_str();

    SDL_Color black = {0,0,0,255};
    m_pImage = TTF_RenderText_Blended( m_pFont, str, black );

    m_Rect.x = 800 - m_pImage->w;
}
