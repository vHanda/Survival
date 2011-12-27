#ifndef TIMER_H
#define TIMER_H

#include "Image/SDL_SurfacePtr.h"
#include <SDL/SDL_ttf.h>

class Timer
{
private :
    enum State {
        state_run,
        state_pause
    };

    State m_State;
    float m_fSecTime;
    int m_iTotalTime;
    TTF_Font * m_pFont;
    SDL_SurfacePtr m_pImage;
    SDL_Rect m_Rect;

    void renderTime();

public:
    Timer();
    virtual ~Timer();

    void init();
    void deinit();

    void update(float timeElapsed);
    void render();

    void setPos(int y)
    { m_Rect.y = y; }

    void pause() { m_State = state_pause; }
    void run() { m_State = state_run; }

    int time() { return m_iTotalTime; }
    std::string get() const;
};

#endif // TIMER_H
