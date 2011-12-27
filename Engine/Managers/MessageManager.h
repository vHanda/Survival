#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <set>
class Message;

class MessageManager
{
private :
    std::set<Message> m_PQ;

    MessageManager();
    ~MessageManager();

public :
    void add(const Message & m);
    void update(float timeElapsed);

    static MessageManager * instance()
    {
        static MessageManager mm;
        return &mm;
    }
};

#endif // MESSAGEMANAGER_H
