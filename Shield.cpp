#include "Shield.h"
#include "World.h"
#include "Engine/ErrorHandler.h"
#include "tinyxml/tinyxml.h"
#include "Monster.h"
#include "Engine/Managers/EffectManager.h"

Shield::Shield(Agent * a, shield_type st, const b2Vec2 & startPos, const b2Vec2 & dir)
: Projectile(a, startPos, dir), m_Type(st)
{
}

Shield::~Shield()
{
    //deinit();
}

void Shield::init()
{
    std::string fileName;
    switch( static_cast<int>(m_Type) )
    {
    case shield_player :
        fileName = "data/shield_player";
        initFromFile(fileName);
        break;

    case shield_monster :
        fileName = "data/shield_monster";
        initFromFile(fileName);
        break;

    default :
        G_THROW("Unknown Case for Shield");
    }
}

void Shield::destructionAnim()
{
    //Get Position
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos *= World::ratio;

    //Create Effect
    Effect *e = new Effect(pos);
    e->getSprite().init("data/sprites/s_explo");

    //Add to the Manager
    EffectManager::instance()->add(e);
}
