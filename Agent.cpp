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
