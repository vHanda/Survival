#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Image/SDL_SurfacePtr.h"
//#include <SDL/SDL_gfxPrimitives.h>
#include "Engine/Keyboard.h"
#include <string>
#include <SDL/SDL_ttf.h>

class TextBox
{
private :
    SDL_SurfacePtr m_pTextImage;

    std::string m_sText;
    TTF_Font * m_pFont;

    SDL_Rect m_Pos;
    SDL_Color m_Color;

    bool m_bDone;

    int m_iTimes;
    SDLKey m_LastKey;
public:
    TextBox();
    virtual ~TextBox();

    void setPos(int x, int y)
    { m_Pos.x = x; m_Pos.y = y; }

    void update(float timeElapsed);
    void render();

    bool done() const { return m_bDone; }
    std::string get() const { return m_sText; }
};

#endif // TEXTBOX_H
