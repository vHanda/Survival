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

#include "Agent.h"
#include "Engine/Engine.h"
#include "Projectile.h"
#include <SDL/SDL_rotozoom.h>
#include "Map.h"
#include <Box2D/Box2D.h>

Agent::Agent(Map * pMap)
: Box2DEntity(pMap->getWorld()), m_pMap(pMap)
{
}

void Agent::initFromXMLFile(std::string fileName,const b2Vec2 & startPos)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();
    TiXmlElement * pRoot = doc.RootElement();

    if(pRoot->ValueStr() != "agent")
        G_THROW("Agent xml file Problem");

    TiXmlElement * pElement = pRoot->FirstChildElement("image");
    m_pImage = load_image(pElement->GetText());

    //Box2D
    TiXmlElement * pBox = pRoot->FirstChildElement("box2d");
    b2BodyDef bodyDef;
    bodyDef.position = startPos;
    bodyDef.allowSleep = false;
    bodyDef.userData = this;

    //std::cout << "Creating body" << std::endl;
    m_pBody = m_pWorld->CreateBody(&bodyDef);

    b2CircleDef sDef;
    sDef.radius = (m_pImage->w/2) / World::ratio;
    getShape(pBox, sDef);

    m_pBody->CreateShape( &sDef );
    m_pBody->SetMassFromShapes();

    //Fire timings
    m_fBulletDelay = atof(pRoot->FirstChildElement("bulletTime")->GetText());
    m_fShieldDelay = atof(pRoot->FirstChildElement("shieldTime")->GetText());

    m_fBulletTime = 0.0f;
    m_fShieldTime = 0.0f;

    //Speed and life.
    m_fSpeed = atof(pRoot->FirstChildElement("speed")->GetText());
    m_fMaxLife = atof(pRoot->FirstChildElement("life")->GetText());
    m_fLife = m_fMaxLife;
}


void Agent::handleProjectile(Projectile * proj)
{
    m_fLife -= proj->getDamage();
}
