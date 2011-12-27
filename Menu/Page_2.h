#ifndef PAGE_2_H
#define PAGE_2_H

#include "Page.h"

class Page_2 : public Page
{
private :
    enum state {
        state_left,
        state_right
    };

    SDL_SurfacePtr m_pPlayer;
    SDL_Rect m_Pos;
    state m_State;
public:
    Page_2();
    virtual ~Page_2();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_2_H
