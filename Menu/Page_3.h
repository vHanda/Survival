#ifndef PAGE_3_H
#define PAGE_3_H

#include "Page.h"
#include <vector>
#include <Box2D/Box2D.h>

class Page_3 : public Page
{
private :
    enum state {
        state_left,
        state_right
    };

    SDL_SurfacePtr m_pPlayer;
    SDL_SurfacePtr m_pBulletImage;
    SDL_Rect m_Pos;
    state m_State;

    struct Bullet {
        SDL_Rect pos;
        b2Vec2 vel;
    };

    std::vector<Bullet> m_List;
    float m_fBulletDelay;
public:
    Page_3();
    virtual ~Page_3();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_3_H
