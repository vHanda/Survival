#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "FSM/State.h"
#include "Game.h"
#include "Engine/Effect.h"
#include "TextBox.h"

class Game_Init : public State<Game> {
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Play : public State<Game> {
private :
    Mix_Music * m_pMusic;
    SDL_SurfacePtr m_pPausedImage;

    enum state {
        state_run,
        state_pause
    };

    state m_State;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Death : public State<Game> {
private :
    Sprite m_Sprite;
    SoundEffect m_SoundEffect;
    b2Vec2 m_Pos;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

class Game_Highscore : public State<Game> {
private :
    SDL_SurfacePtr m_pImage;
    SDL_Rect m_Rect;
    TextBox m_TextBox;

    void addToHighscores(Game * g) const;
public :
    void enter(Game * g);
    void update(Game * g, float timeElapsed);
    void render(Game * g);
    void exit(Game * g);
    bool handleMessage(Game * g, const Message & m){return false;}
};

#endif // GAMESTATES_H
