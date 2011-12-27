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

#ifndef BOX2DENTITY_H
#define BOX2DENTITY_H

#include "Engine/Entity.h"
#include "Camera.h"
#include "Box2D/Box2D.h"
#include "Image/SDL_SurfacePtr.h"
#include "tinyxml/tinyxml.h"

class Box2DEntity : public Entity
{
public:
    Box2DEntity(b2World * pWorld, int id=-1)
    : Entity(id), m_pBody(NULL), m_pWorld(pWorld)
    {m_fMinAngle = 5; m_fAngle=0.0f;}

    virtual ~Box2DEntity() {deinit();}

    //Pure Virtual Functions
    virtual void init() = 0;
    virtual void deinit();

    virtual void update(float timeElapsed)=0;
	virtual void render() =0;
    virtual bool handleMessage(const Message & msg) = 0;

    b2Body * getBody() const { return m_pBody; }

protected:
    b2Body * m_pBody;
    b2World * m_pWorld;

    void adjustAngle(SDL_SurfacePtr & s);
    void setMinAngle(float a) { m_fMinAngle = a; }
private:
    //The angles are in degrees
    float m_fAngle;
    float m_fMinAngle;
};


//Renders a surface according to the body pos
inline void render_Box2DEntity(SDL_Surface * surface, b2Body * body)
{
    SDL_Surface * screen = SDL_GetVideoSurface();

    SDL_Rect rect;
    rect.x = body->GetWorldCenter().x * World::ratio - surface->w/2;
    rect.y = body->GetWorldCenter().y * World::ratio - surface->h/2;
    transform_Camera(rect);
    SDL_BlitSurface( surface, NULL, screen, &rect);
}

inline void getShape(TiXmlElement * pBox, b2ShapeDef & sDef)
{
    sDef.density = atof( pBox->FirstChildElement("density")->GetText());
    sDef.friction = atof( pBox->FirstChildElement("friction")->GetText());
    sDef.restitution = atof( pBox->FirstChildElement("restitution")->GetText());
}
#endif // BOX2DENTITY_H
