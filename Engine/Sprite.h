#ifndef SPRITE_H
#define SPRITE_H

#include "../Image/SDL_SurfacePtr.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <Box2D/Box2D.h>
#include "../tinyxml/tinyxml.h"

class Sprite
{
public:
    Sprite(std::string fileName="", int fps = 5);
    virtual ~Sprite();

    void update(float timeElapsed);
    void render(const b2Vec2 & pos);

    void addSurface(SDL_Surface * surface)
    { assert(surface != 0); m_Sprites.push_back( new SDL_SurfacePtr(surface) ); }

    bool done()
    { return m_bDone; }

    SDL_SurfacePtr & operator[](boost::ptr_vector<SDL_SurfacePtr>::size_type n)
    { if(n<m_Sprites.size()) return m_Sprites[n]; return m_Sprites[0];}

    enum playType {
        play_loop,
        play_once,
        play_dont
    };

    void setPlayType(playType p) { m_PlayType = p; }
    playType getPlayType() { return m_PlayType; }

    void init(TiXmlElement * pElement);
    void init(std::string fileName);

    void setFPS(int fps);
    void zoom(float ratio);
protected:
private:
    boost::ptr_vector<SDL_SurfacePtr> m_Sprites;
    int m_iFrameNo;
    int m_iFPS;
    float m_fDelay;
    float m_fTotalTime;
    bool m_bDone;

    playType m_PlayType;
};

#endif // SPRITE_H
