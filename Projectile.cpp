#include "Projectile.h"
#include "World.h"
#include <SDL/SDL_rotozoom.h>
#include "Agent.h"

Projectile::Projectile(Agent * a, const b2Vec2 & startPos, const b2Vec2 & dir)
:   Box2DEntity(a->getBody()->GetWorld()),
    m_StartPos(startPos), m_Dir(dir), m_pOwner(a)
{
}

Projectile::~Projectile()
{
    //deinit();
}

void Projectile::init()
{
}

void Projectile::update(float timeElapsed)
{
    m_fLife -= timeElapsed;
}

void Projectile::render()
{
    adjustAngle(m_pImage);
    render_Box2DEntity( m_pImage.get(), m_pBody );
}

void Projectile::initFromFile(const std::string & fileName)
{

    TiXmlDocument doc(fileName.c_str());
    doc.LoadFile();

    TiXmlElement * pRoot = doc.FirstChildElement();
    TiXmlElement * pElement = pRoot;

    //The force and size are constant
    m_pImage = load_image( pElement->FirstChildElement("image")->GetText() );
    m_fSpeed = atof(pElement->FirstChildElement("speed")->GetText());
    m_fLife  = atof(pElement->FirstChildElement("life")->GetText());
    m_fDamage= atof(pElement->FirstChildElement("damage")->GetText());

    //Box2D
    TiXmlElement * pBox = pElement->FirstChildElement("box2d");

    b2BodyDef bodyDef;
    bodyDef.isBullet = true;
    bodyDef.position = m_StartPos;
    bodyDef.userData = this;

    m_pBody = m_pWorld->CreateBody( &bodyDef );

    b2CircleDef sDef;
    sDef.radius = ((float)m_pImage->w/2) / World::ratio;
    getShape(pBox, sDef);

    m_pBody->CreateShape(&sDef);
    m_pBody->SetMassFromShapes();

    if(m_Dir.LengthSquared() != 1.0f)
        m_Dir.Normalize();

    //Apply the velocity
    b2Vec2 vel = m_Dir;
    vel *= m_fSpeed;
    m_pBody->SetLinearVelocity(vel);
}

