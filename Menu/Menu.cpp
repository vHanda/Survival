#include "Menu.h"
#include "../Game.h"
#include "../Engine/Mouse.h"

#include "Credits.h"
#include "Help.h"
#include "Highscore.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::enter(App * a)
{
    //
    //Title
    //
    //Open Font and render Image on temp surface
    m_pImage = SDL_CreateRGBSurface(800,600);
    SDL_FillRect(m_pImage.get(), NULL, 0xFFFFFFFF);

    TTF_Font * pFont = TTF_OpenFont("data/fonts/BEARPAW_.TTF",168);
    SDL_Color blackColor = {0,0,0,0};
    SDL_SurfacePtr title = TTF_RenderText_Blended(pFont, "Survival", blackColor);
    TTF_CloseFont(pFont);

    SDL_Rect rect;
    rect.x = 800/2 - title->w/2;
    rect.y = 50;
    //Render temp surface on background image
    SDL_BlitSurface( title.get(), NULL, m_pImage.get(), &rect);

    //
    //Menu
    //
    m_Color = blackColor;

    m_vOptions.push_back("New Game");
    m_vOptions.push_back("High Scores");
    m_vOptions.push_back("Help");
    m_vOptions.push_back("Credits");
    m_vOptions.push_back("Quit");

    m_pFont = TTF_OpenFont("data/fonts/Ayuma2yk.ttf", 40);
    m_pBiggerFont = TTF_OpenFont("data/fonts/Ayuma2yk.ttf", 68);

    m_Rect.w = 400;
    m_Rect.h = 400;
    m_Rect.x = 800/2 - m_Rect.w/2;
    m_Rect.y = 250;

    m_IndivRect.w = 400;
    m_IndivRect.h = 60;

    m_pCursorImage = load_image("data/gfx/menu/cursor.png");
    m_pMenuImage = SDL_CreateRGBSurface(m_Rect.w, m_Rect.h);
    SDL_FillRect(m_pMenuImage.get(), NULL, 0xFFFFFFFF);

    m_fKeyDelay = KeyDelay;
    m_iPos = 0;

    //Render meu back
    m_pMenuBackImage= load_image("data/gfx/menu/menu_back.png");

    renderMenu();
}

void Menu::update(App * a, float timeElapsed)
{
    bool redraw = false;
    //Mouse motion
    int mp = getMousePos();
    if( mp != -1 && mp != m_iPos )
    {
        m_iPos = mp;
        redraw = true;
    }

    m_fKeyDelay -= timeElapsed;
    if( m_fKeyDelay <= 0.0f )
    {
        if(a->isKeyDown( SDLK_UP ))
        {
            m_iPos--;
            m_fKeyDelay = KeyDelay;
            redraw = true;
        }
        else if(a->isKeyDown( SDLK_DOWN ))
        {
            m_iPos++;
            m_fKeyDelay = KeyDelay;
            redraw = true;
        }

        //Bounds Checking
        if( m_iPos == -1) m_iPos = m_vOptions.size()-1;
        if( m_iPos == m_vOptions.size()) m_iPos = 0;
    }

    renderMenu();

    if(a->isKeyDown(SDLK_RETURN) || a->isKeyDown(SDLK_SPACE))
        handleMenu(a);
    if(mp != -1 && a->isMouseDown(1))
        handleMenu(a);

}

void Menu::render(App * a)
{
    SDL_Surface * screen = SDL_GetVideoSurface();

    //Render title
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL);
    //Render menu
    SDL_Rect rect;
    rect.x = m_Rect.x + 40;
    rect.y = m_Rect.y - 20;
    SDL_BlitSurface( m_pMenuImage.get(), NULL, screen, &m_Rect);
    SDL_BlitSurface( m_pMenuBackImage.get(), NULL, screen, &rect);

    //Render miscellaneous
    //TODO :
}
void Menu::exit(App * a)
{
    TTF_CloseFont(m_pFont);
    TTF_CloseFont(m_pBiggerFont);
}

void Menu::renderMenu()
{
    if( m_iPos < 0 ) return;
    if( m_iPos >= m_vOptions.size() ) return;

    SDL_FillRect(m_pMenuImage.get(), NULL, 0xFFFFFFFF);

    SDL_Rect rect;
    rect.y = 0;
    //Render alll the options except the chosen one.
    for(unsigned int i=0; i<m_vOptions.size(); i++)
    {
        if(i != m_iPos)
        {
            SDL_SurfacePtr temp = TTF_RenderText_Blended(m_pFont, m_vOptions[i].c_str(), m_Color);
            rect.x = m_Rect.w/2 - temp->w/2;
            SDL_BlitSurface( temp.get(), NULL, m_pMenuImage.get(), &rect);
        }
        else
            rect.y += 10;
        rect.y += m_IndivRect.h;
    }

    //Render the chosen option with the bigger font.
    SDL_SurfacePtr temp = TTF_RenderText_Blended(m_pBiggerFont, m_vOptions[m_iPos].c_str(), m_Color);
    rect.x = m_Rect.w/2 - temp->w/2;
    rect.y = m_IndivRect.h * m_iPos - 5;
    SDL_BlitSurface( temp.get(), NULL, m_pMenuImage.get(), &rect);

    //Render the cursor
    rect.x = m_Rect.w/2 - m_pCursorImage->w/2;
    //rect.y -= 10/2;
    SDL_BlitSurface( m_pCursorImage.get(), NULL, m_pMenuImage.get(), &rect);
}

int Menu::getMousePos()
{
    int x,y;
    Mouse::getInstance()->getPos(x,y);

    x-= m_Rect.x;
    y-= m_Rect.y;
    if(x < 0 || y < 0)  return -1;
    if(x > m_Rect.w || y > m_Rect.w) return -1;

    int pos = y/m_IndivRect.h;
    return pos;
}

void Menu::handleMenu(App * a)
{
    switch( m_iPos )
    {
    case 0 :
        a->getFSM()->changeState( new Game );
        return;
    case 1 :
        a->getFSM()->changeState( new HighScores );
        return;
    case 2 :
        a->getFSM()->changeState( new Help );
        break;
    case 3 :
        a->getFSM()->changeState( new Credits );
        break;
    case 4 :
        a->quit();
        break;
    }
}
