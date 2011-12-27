/*
 * Survival
 *
 * Copyright (C) 2009-2011 Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
