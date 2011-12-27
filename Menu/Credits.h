#ifndef CREDITS_H
#define CREDITS_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <SDL/SDL_ttf.h>
#include "../App.h"

class Credits : public State<App>
{
    SDL_SurfacePtr m_pImage;
    SDL_SurfacePtr m_pLeftArrow;
public :
    Credits();
    ~Credits();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};

#endif // CREDITS_H
