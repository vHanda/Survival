#include "GameStates.h"
#include "Engine/Managers/EffectManager.h"
#include "Engine/Keyboard.h"
#include "Camera.h"
#include <SDL/SDL_mixer.h>
#include "Score_func.h"
#include <algorithm>
//
//Init
//

void Game_Init::enter(Game * g)
{
}

void Game_Init::update(Game * g, float timeElapsed)
{
    g->getFsm()->changeState( new Game_Play() );
}

void Game_Init::render(Game * g)
{
}

void Game_Init::exit(Game * g)
{
}

//
//Play
//
void Game_Play::enter(Game * g)
{
    m_pMusic = Mix_LoadMUS("data/sfx/piR8_deal_light.ogg");
    Mix_PlayMusic(m_pMusic, -1);

    g->getTimer()->run();
    m_State = state_run;
    m_pPausedImage = load_image("data/gfx/paused.png");
}

void Game_Play::update(Game * g, float timeElapsed)
{
    if( m_State == state_pause )
    {
        Keyboard * kb = Keyboard::getInstance();
        if( kb->isDown(SDLK_p) )
        {
            m_State = state_run;
            SDL_Delay(200);
        }
        return;
    }

    //World
    static const float32 timeStep = 1.0f / 60.0f;
    static const int32 iterations = 10;
    g->getWorld()->Step(timeStep, iterations, iterations);

    //Entities
    g->getMap()->update(timeElapsed);
    g->getPlayer()->update(timeElapsed);
    g->getMonsters()->update(timeElapsed);

    //Managers
    EffectManager::instance()->update(timeElapsed);
    Camera::getInstance()->update(timeElapsed);

    //State Change
    if( g->getPlayer()->done() == true )
        g->getFsm()->changeState( new Game_Death );

    if( Keyboard::getInstance()->isDown(SDLK_p) )
    {
        m_State = state_pause;
        SDL_Delay(200);
    }
}

void Game_Play::render(Game * g)
{
    g->getMap()->render();
    g->getPlayer()->render();
    g->getMonsters()->render();

    EffectManager::instance()->render();

    if( m_State == state_pause )
    {
        SDL_Rect rect;
        rect.x = 800/2 - m_pPausedImage->w/2;
        rect.y = 600/2 - m_pPausedImage->h/2;
        SDL_BlitSurface(m_pPausedImage.get(), NULL, SDL_GetVideoSurface(), &rect);
    }
}

void Game_Play::exit(Game * g)
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_pMusic);

    g->getTimer()->pause();
}

//
//Death
//
void Game_Death::enter(Game * g)
{
    m_Sprite.init("data/sprites/player_death_sprite");

    m_Pos = g->getPlayer()->getBody()->GetWorldCenter();
    m_Pos *= World::ratio;
    transform_Camera(m_Pos);

    //m_SoundEffect.init("data/sfx/crowdohh.ogg");
    //m_SoundEffect.play();
}

void Game_Death::update(Game * g, float timeElapsed)
{
    //Managers
    EffectManager::instance()->update(timeElapsed);
    Camera::getInstance()->update(timeElapsed);

    //Sprite
    m_Sprite.update(timeElapsed);

    if(m_Sprite.done() && m_SoundEffect.done())
        g->getFsm()->changeState(new Game_Highscore);

}

void Game_Death::render(Game * g)
{
    g->getMap()->render();
    g->getMonsters()->render();
    EffectManager::instance()->render();

    m_Sprite.render(m_Pos);
}

void Game_Death::exit(Game * g)
{
    SDL_Delay(500);
}

//
//Highscore
//
void Game_Highscore::enter(Game * g)
{
    m_pImage = load_image("data/gfx/highscore_game.png");

    std::stringstream ss;
    ss << g->getMonsters()->killed() << " killed in " << g->getTimer()->get();
    std::string str = ss.str();

    TTF_Font * pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF",35);
    SDL_Color white = {255,255,255,255};
    SDL_SurfacePtr textImage = TTF_RenderText_Blended(pFont, str.c_str(), white);
    TTF_CloseFont(pFont);

    SDL_Rect rect;
    rect.x = 115;
    rect.y = 75;
    SDL_BlitSurface( textImage.get(), NULL, m_pImage.get(), &rect);

    pFont = TTF_OpenFont("data/fonts/CHICSA__.TTF", 50);
    textImage = TTF_RenderText_Blended(pFont, "Name : ", white);
    TTF_CloseFont(pFont);

    rect.x = 25;
    rect.y = 130;
    SDL_BlitSurface( textImage.get(), NULL, m_pImage.get(), &rect);

    //Set the textBox
    m_Rect.x = 800/2 - m_pImage->w/2;
    m_Rect.y = 600/2 - m_pImage->h/2;
    m_TextBox.setPos( m_Rect.x + 145, m_Rect.y + 130 );

}

void Game_Highscore::update(Game * g, float timeElapsed)
{
    m_TextBox.update(timeElapsed);
    if( m_TextBox.done() )
    {
        addToHighscores(g);
        g->done();
    }
}

void Game_Highscore::render(Game * g)
{
    g->getMap()->render();
    g->getMonsters()->render();
    EffectManager::instance()->render();

    //Highscore
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, &m_Rect );

    m_TextBox.render();
}

void Game_Highscore::exit(Game * g)
{
    SDL_Delay(200);
}

void Game_Highscore::addToHighscores(Game * g) const
{
    hScore sc;
    sc.name = m_TextBox.get();
    sc.killed = g->getMonsters()->killed();
    sc.time =  g->getTimer()->time();

    //std::cout << sc.name << " " << sc.killed << " " << sc.time << std::endl;
    if( sc.name == "" )
        sc.name = "No Name";

    std::vector<hScore> list;
    load_score(list);
    list.push_back(sc);
    std::sort(list.rbegin(), list.rend());
    list.resize(5);

    save_score(list);
}
