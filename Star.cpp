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

#include "Star.h"
#include "tinyxml/tinyxml.h"
#include "Engine/Engine.h"
#include "Engine/Managers/EffectManager.h"

Star::Star(b2World * pWorld, const b2Vec2 & startPos)
: Box2DEntity(pWorld), m_StartPos(startPos)
{
    //ctor
}

Star::~Star()
{
    //deinit();
}

void Star::init()
{
    //Take values from xml file
    TiXmlDocument doc("data/star");
    doc.LoadFile();
    TiXmlElement * pRoot = doc.RootElement();
    if(pRoot->ValueStr() != "star")
        G_THROW("Star xml file Problem");

    TiXmlElement * pElement = pRoot->FirstChildElement("image");
    m_pImage = load_image( pElement->GetText() );

    pElement = pRoot->FirstChildElement("life");
    m_fLife = atoi(pElement->GetText());

    //Create the body
    b2BodyDef bodyDef;
    bodyDef.position = m_StartPos;
    bodyDef.userData = this;

    m_pBody = m_pWorld->CreateBody( &bodyDef );

    b2CircleDef sDef;
    sDef.radius = ((float)m_pImage->w/2) / World::ratio;
    sDef.isSensor = true;
    m_pBody->CreateShape(&sDef);

    //State
    m_State = state_normal;
    m_Sprite.init("data/sprites/star_death");
}


void Star::update(float timeElapsed)
{
    m_fLife -= timeElapsed;
    if( m_fLife <= 1.0)
    {
        m_State = state_invisible;
        m_Sprite.update(timeElapsed);
    }
}

void Star::render()
{
    if( m_State == state_normal )
        render_Box2DEntity( m_pImage.get(), m_pBody );
    else
    {
        b2Vec2 pos = m_pBody->GetWorldCenter();
        pos *= World::ratio;
        transform_Camera(pos);
        m_Sprite.render( pos );
    }
}

void Star::destructionAnim()
{
    //Get Position
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos *= World::ratio;

    //Create Effect
    Effect *e = new Effect(pos);
    e->getSprite().init("data/sprites/star_collect");

    //Add to the Manager
    EffectManager::instance()->add(e);
}
