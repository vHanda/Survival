#ifndef SCORE_H
#define SCORE_H

#include "Image/SDL_SurfacePtr.h"
#include <SDL/SDL_ttf.h>

class ScoreBoard
{
private :
    int m_iKilled;

    TTF_Font * m_pFont;
    SDL_SurfacePtr m_pImage;
    SDL_Rect m_Rect;

    void renderScore();
public:
    ScoreBoard();
    virtual ~ScoreBoard();

    void init();
    void deinit();

    void update(int kills);
    void render();

    void setPos(int y)
    { m_Rect.y = y; }
};

#endif // SCORE_H
