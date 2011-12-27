#ifndef PAGE_H
#define PAGE_H

#include "../Image/SDL_SurfacePtr.h"

class Page
{
protected :
    SDL_SurfacePtr m_pImage;
public:
    Page();
    virtual ~Page();

    virtual void update(float timeElapsed);
    virtual void render();
};

#endif // PAGE_H
