#ifndef PAGE_4_H
#define PAGE_4_H

#include "Page.h"
#include <vector>
#include <Box2D/Box2D.h>

class Page_4 : public Page
{
private :
    enum state {
        state_left,
        state_right
    };

    SDL_SurfacePtr m_pPlayer;
    SDL_SurfacePtr m_pShieldImage;
    SDL_Rect m_Pos;
    state m_State;

    struct Shield {
        SDL_Rect pos;
        b2Vec2 vel;
    };

    std::vector<Shield> m_List;
    float m_fShieldDelay;
public:
    Page_4();
    virtual ~Page_4();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_4_H
