#ifndef Map_H
#define Map_H

#include <string>
#include <vector>
#include "Image/SDL_SurfacePtr.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <Box2D/Box2D.h>

class Bullet;
class Shield;
class Star;
class Obstacle;

class Map
{
private :
    SDL_SurfacePtr m_pSurface;
    int m_iWidth;
    int m_iHeight;

    boost::ptr_list<Bullet> m_Bullets;
    boost::ptr_list<Shield> m_Shields;
    boost::ptr_list<Star> m_Stars;
    boost::ptr_list<Obstacle> m_Obstacles;

    void createMap();
    void createMapBounderies();

    b2World * m_pWorld;
public:
    Map(b2World * pWorld);
    virtual ~Map();

    void init();
    void deinit();

    void render();
    void update(float timeElapsed);

    int getWidth() const { return m_iWidth; }
    int getHeight() const { return m_iHeight; }
    b2World * getWorld() const { return m_pWorld; }

    void addBullet(Bullet * b);
    void addShield(Shield * s);
    void addStar(Star * s);
};

#endif // Map_H
