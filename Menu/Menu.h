#ifndef MENU_H
#define MENU_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>
#include "../App.h"

class Menu : public State<App>
{
    SDL_SurfacePtr m_pImage;
    SDL_SurfacePtr m_pMenuImage;
    SDL_SurfacePtr m_pCursorImage;
    SDL_SurfacePtr m_pMenuBackImage;

    SDL_Rect m_Rect;
    SDL_Rect m_IndivRect;

    SDL_Color m_Color;

    int m_iPos;
    std::vector<std::string> m_vOptions;

    TTF_Font * m_pFont;
    TTF_Font * m_pBiggerFont;

    float m_fKeyDelay;
    const static float KeyDelay = SDL_DEFAULT_REPEAT_DELAY/1000.0f;

    void renderMenu(); //Renders the options along with the cursor on MenuImage
    int getMousePos();
    void handleMenu(App * a);
public :
    Menu();
    ~Menu();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};

#endif // MENU_H
