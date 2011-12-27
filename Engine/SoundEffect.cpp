#include "SoundEffect.h"
#include "ErrorHandler.h"

SoundEffect::SoundEffect(Mix_Chunk * chunk)
: m_Sound(chunk)
{
    //ctor
    m_iChannelNo = -1;
}

SoundEffect::SoundEffect(std::string fileName)
{
    init(fileName);
}

void SoundEffect::init(std::string fileName)
{
    m_Sound = Mix_LoadWAV(fileName.c_str());
    if(m_Sound == NULL)
        G_THROW(fileName + " could not be opened");
    m_iChannelNo = -1;
}

SoundEffect::~SoundEffect()
{
    //dtor
    Mix_FreeChunk( m_Sound );
}

void SoundEffect::play(int loops)
{
    m_iChannelNo = Mix_PlayChannel( -1, m_Sound, loops);
    Mix_Volume(m_iChannelNo, MIX_MAX_VOLUME/3);
}

bool SoundEffect::done()
{
    if( Mix_Playing( m_iChannelNo ) == false )
        return true;
    return false;
}
