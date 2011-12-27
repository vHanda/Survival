#ifndef PAGE_5_H
#define PAGE_5_H

#include "Page.h"
#include "../Engine/Sprite.h"

class Page_5 : public Page
{
private :
    Sprite m_Sprite;
public:
    Page_5();
    virtual ~Page_5();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_5_H
