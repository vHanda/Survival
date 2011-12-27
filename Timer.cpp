#include "Timer.h"
#include <string>
#include <sstream>

Timer::Timer()
{
    //ctor
}

Timer::~Timer()
{
    //dtor
    deinit();
}

void Timer::init()
{
    m_fSecTime = 0.0f;
    m_iTotalTime = 0;
    m_pFont = TTF_OpenFont("data/fonts/BEARPAW_.TTF", 50);

    m_Rect.x = 0;
    m_Rect.y = 0;

    m_State = state_pause;

    //Render 00:00 onto the surface
    renderTime();
}

void Timer::deinit()
{
    if(m_pFont != NULL)
    {
        TTF_CloseFont(m_pFont);
        m_pFont = NULL;
    }
}

void Timer::update(float timeElapsed)
{
    if( m_State == state_run )
    {
        m_fSecTime += timeElapsed;
        if(m_fSecTime >= 1.0)
        {
            m_fSecTime = 0.0f;
            m_iTotalTime += 1;
            renderTime();
        }
    }
}
void Timer::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, &m_Rect);
}

void Timer::renderTime()
{
    const char * str = get().c_str();

    SDL_Color black = {0,0,0,255};
    m_pImage = TTF_RenderText_Blended( m_pFont, str, black );

    m_Rect.x = 800 - m_pImage->w;
}

std::string Timer::get() const
{
    std::stringstream ss;
    int min = m_iTotalTime / 60;
    if( min < 10 )
        ss << "0";
    ss << min << ":";

    int sec = m_iTotalTime % 60;
    if(sec < 10)
        ss << "0";
    ss << sec;

    return ss.str();
}
