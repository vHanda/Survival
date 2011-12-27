#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED

#include "State.h"
#include <cstdio>
#include <memory>

class Message;

template <typename entity_type>
class StateMachine {
    entity_type * m_pOwner;

    std::auto_ptr<State<entity_type> > m_pCurrentState;
    std::auto_ptr<State<entity_type> > m_pGlobalState;
	std::auto_ptr<State<entity_type> > m_pPrevState;
public :

	StateMachine(entity_type * owner)
	: m_pOwner(owner)
	{
	}

	virtual ~StateMachine()
	{
	    /*if( m_pCurrentState != NULL )
            delete m_pCurrentState;
        if( m_pGlobalState != NULL )
            delete m_pGlobalState;
        if( m_pPrevState != NULL )
            delete m_pPrevState;*/
	}
    State<entity_type> * getGlobalState() const { return m_pGlobalState.get(); }
    State<entity_type> * getCurrentState() const { return m_pCurrentState.get(); }
    State<entity_type> * getPrevState() const { return m_pPrevState.get(); }

    void changeState(State<entity_type> * st);
	void update(float timeElapsed);
    void render();
    bool handleMessage(const Message & m);

    void setGlobalState(State<entity_type> * state)
    { m_pGlobalState = std::auto_ptr<State<entity_type> >(state); }

    void setCurrentState(State<entity_type> * state)
    { m_pCurrentState = std::auto_ptr<State<entity_type> >(state); }

    void revertToPrevState()
    {
    	changeState( m_pPrevState );
    }

    void clear()
    {
        if(m_pCurrentState.get() != NULL)
            m_pCurrentState->exit(m_pOwner);
    }
};

template<typename entity_type>
void StateMachine<entity_type>::changeState(State<entity_type> * st)
{
	if(st == NULL)
		return;

	if(m_pCurrentState.get() != NULL)
	{
    	m_pCurrentState->exit(m_pOwner);
        m_pPrevState.reset();
    	m_pPrevState = m_pCurrentState;
    }

    m_pCurrentState = std::auto_ptr<State<entity_type> >(st);
    m_pCurrentState->enter(m_pOwner);
}

template<typename entity_type>
void StateMachine<entity_type>::update(float timeElapsed)
{
	if(m_pGlobalState.get() != NULL)
		m_pGlobalState->update(m_pOwner, timeElapsed);

	if(m_pCurrentState.get() != NULL)
		m_pCurrentState->update(m_pOwner, timeElapsed);
}

template<typename entity_type>
void StateMachine<entity_type>::render()
{
	if(m_pGlobalState.get() != NULL)
		m_pGlobalState->render(m_pOwner);

	if(m_pCurrentState.get() != NULL)
		m_pCurrentState->render(m_pOwner);
}

template<typename entity_type>
bool StateMachine<entity_type>::handleMessage(const Message & m)
{
	if(m_pGlobalState.get() != NULL)
        if( m_pGlobalState->handleMessage(m_pOwner, m) )
            return true;

	if(m_pCurrentState.get() != NULL)
		if( m_pCurrentState->handleMessage(m_pOwner, m) )
            return true;

    return false;
}


#endif // STATEMACHINE_H_INCLUDED
