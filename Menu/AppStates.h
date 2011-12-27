#ifndef APPSTATES_H
#define APPSTATES_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>

class App;

class Intro : public State<App>
{
public :
    Intro();
    ~Intro();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};






#endif // APPSTATES_H
