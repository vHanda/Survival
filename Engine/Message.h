#ifndef MESSAGE_H
#define MESSAGE_H
#include <SDL/SDL.h>

class Message {
private :
    static int iLeastDiff;
public :
    int from, to;
    int message;
    float timeDelay;
    void * data;
    int timeSent;

    Message(int f, int t, int m, float tD = 0.0f, void * d=0)
    : from(f), to(t), message(m), timeDelay(tD), data(d)
    { timeSent= SDL_GetTicks() + iLeastDiff++;}

    virtual ~Message() {}

    bool operator <(const Message & rhs) const
    {
        if(timeDelay == rhs.timeDelay)
        {
            if(timeSent == rhs.timeSent)
                assert( !"Damn Messages not unique" );
            return timeSent < rhs.timeSent;
        }
        return timeDelay < rhs.timeDelay;
    }
    bool operator ==(const Message & rhs) const
    {
        return from == rhs.from && to==rhs.to && message == rhs.message &&
                timeDelay == rhs.timeDelay && timeSent==rhs.timeSent;
    }
};

#endif
