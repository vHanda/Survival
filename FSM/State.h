#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

class Message;

template <typename T>
class State {
public :
    State() {}
    virtual ~State() {}

    virtual void enter(T * a) = 0;
    virtual void update(T * a, float timeElapsed) = 0;
    virtual void render(T * a) =0;
    virtual void exit(T * a) = 0;
    virtual bool handleMessage(T * a, const Message & m) = 0;
};

#endif // STATE_H_INCLUDED
