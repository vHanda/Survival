#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL/SDL_mixer.h>
#include <string>

class SoundEffect
{
public:
    SoundEffect(Mix_Chunk * chunk = NULL);
    SoundEffect(std::string fileName);
    virtual ~SoundEffect();

    void play(int loops = 0);
    bool done();
    void assign(Mix_Chunk * chunk)
    { if(!m_Sound) m_Sound = chunk; }
    void init(std::string fileName);

    Mix_Chunk* getChunk() { return m_Sound; }
protected:

private:
    Mix_Chunk * m_Sound;
    int m_iChannelNo;
};

#endif // SOUNDEFFECT_H
