#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>

class App;
class hScore;

class HighScores : public State<App>
{
    SDL_SurfacePtr m_pImage;
    SDL_SurfacePtr m_pLeftArrow;

    std::string createString(int i, const hScore & h);
    std::string timeString(int time);
public :
    HighScores();
    ~HighScores();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};


#endif // HIGHSCORE_H
