#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "../Effect.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <map>
#include <SDL/SDL_mixer.h>

class EffectManager
{
private:
    EffectManager();
    virtual ~EffectManager();

    boost::ptr_list<Effect> m_List;
public :
    static EffectManager * instance() { static EffectManager em; return &em; }

    void add(Effect * effect)
    { m_List.push_back(effect); effect->getSoundEffect().play();}

	void add(Mix_Chunk * chunk)
	{ Effect * e = new Effect(); e->addSound(chunk); add(e); }

    void remove(Effect * effect)
    {assert(!"Not Implemented - Removal of Effects");}

    void update(float timeElapsed);
    void render();

    void clear()
    { m_List.clear(); Mix_HaltChannel(-1);}

    void pause()
    { Mix_Pause(-1); }

    void resume()
    { Mix_Resume(-1); }
};

#endif // EFFECT_MANAGER_H
