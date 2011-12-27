#include "EffectManager.h"

EffectManager::EffectManager()
{
    //ctor

}

EffectManager::~EffectManager()
{
    //dtor
}

void EffectManager::render()
{
    typedef boost::ptr_list<Effect>::iterator ELI;
    for(ELI i = m_List.begin(); i!=m_List.end(); i++)
        i->render();
}

void EffectManager::update(float timeElapsed)
{
    //Cleanup
    m_List.erase_if( std::mem_fun_ref(&Effect::done) );

    typedef boost::ptr_list<Effect>::iterator ELI;
    for(ELI i = m_List.begin(); i!=m_List.end(); i++)
        i->update(timeElapsed);
}
