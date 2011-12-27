#include "Help.h"
#include "../App.h"
#include "../Engine/Keyboard.h"
#include "../Engine/Mouse.h"
#include "Menu.h"

#include "Page_1.h"
#include "Page_2.h"
#include "Page_3.h"
#include "Page_4.h"
#include "Page_5.h"

Help::Help()
{

}

Help::~Help()
{

}

void Help::enter(App * a)
{
    //Push required pages
    m_Pages.push_back( new Page_1 );
    m_Pages.push_back( new Page_2 );
    m_Pages.push_back( new Page_3 );
    m_Pages.push_back( new Page_4 );
    m_Pages.push_back( new Page_5 );

    m_iPageNum = 0;

    m_pLeftArrow = load_image("data/gfx/menu/left_arrow.png");
    m_pRightArrow = load_image("data/gfx/menu/right_arrow.png");
    m_pFont = TTF_OpenFont("data/fonts/BEARPAW_.TTF", 60);
    renderPageNum();
}

void Help::update(App * a, float timeElapsed)
{
    m_Pages[m_iPageNum].update(timeElapsed);

    //State Change - Keyboard
    Keyboard * kb = Keyboard::getInstance();
    if( kb->isDown( SDLK_LEFT ) )
    {
        m_iPageNum--;
        if(m_iPageNum < 0)
            a->getFSM()->changeState( new Menu );
        else
            renderPageNum();
    }

    if( kb->isDown( SDLK_RIGHT ) )
    {
        m_iPageNum++;
        if(m_iPageNum >= m_Pages.size())
            a->getFSM()->changeState( new Menu );
        else
            renderPageNum();
    }

    //State Change Mouse
    Mouse * m = Mouse::getInstance();

    if( m->isDown( 1 ) )
    {
        int x,y;
        m->getPos(x, y);
        b2Vec2 pos(x,y);

        //Check for left arrow
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 600 - m_pLeftArrow->h;
        rect.w = m_pLeftArrow->w;
        rect.h = m_pLeftArrow->h;

        if( ct_Rect_Point( rect, pos ) )
        {
            m_iPageNum--;
            if(m_iPageNum < 0)
                a->getFSM()->changeState( new Menu );
            else
                renderPageNum();
        }

        //Check for right arrow
        rect.x = 800 - m_pRightArrow->w;
        rect.y = 600 - m_pRightArrow->h;
        rect.w = m_pRightArrow->w;
        rect.h = m_pRightArrow->h;

        if( ct_Rect_Point( rect, pos ) )
        {
            m_iPageNum++;
            if(m_iPageNum >= m_Pages.size())
                a->getFSM()->changeState( new Menu );
            else
                renderPageNum();
        }

    }

    if( kb->isDown(SDLK_ESCAPE) )
    {
        a->getFSM()->changeState( new Menu );
        return;
    }
}

void Help::render(App * a)
{
    if( m_iPageNum < 0 || m_iPageNum >= m_Pages.size() )
        return;

    m_Pages[m_iPageNum].render();

    SDL_Surface * screen = SDL_GetVideoSurface();

    //Render Page Num and Arrows
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 600 - m_pLeftArrow->h;
    SDL_BlitSurface(m_pLeftArrow.get(), NULL, screen, &rect);

    rect.x = 800 - m_pRightArrow->w;
    rect.y = 600 - m_pRightArrow->h;
    SDL_BlitSurface(m_pRightArrow.get(), NULL, screen, &rect);

    rect.x = 800/2 - m_pPageNum->w/2;
    rect.y = 600 - m_pPageNum->h;
    SDL_BlitSurface(m_pPageNum.get(), NULL, screen, &rect);
}

void Help::exit(App * a)
{
    m_Pages.clear();
    TTF_CloseFont(m_pFont);
}

void Help::renderPageNum()
{
    std::stringstream ss;
    ss << m_iPageNum + 1 << "/" << m_Pages.size();
    std::string str = ss.str();

    SDL_Color blackColor = {0,0,0,0};
    m_pPageNum = TTF_RenderText_Blended(m_pFont, str.c_str(), blackColor);

    //Delay so that page changes are slow.
    SDL_Delay(250);
}
