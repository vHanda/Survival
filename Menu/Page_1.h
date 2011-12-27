#ifndef PAGE_1_H
#define PAGE_1_H

#include "Page.h"


class Page_1 : public Page
{
private :

public:
    Page_1();
    virtual ~Page_1();

    void update(float timeElapsed);
    void render();
};

#endif // PAGE_1_H
