#include "Monster.h"
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Shield.h"
#include "Star.h"
#include "ContactListener.h"
#include "Engine/Managers/EffectManager.h"

Monster::Monster(Map * map, Player * player, NN_File * pBrain)
: Agent(map), m_pPlayer(player), m_pBrain(pBrain)
{}

Monster::~Monster()
{
}

void Monster::init()
{
    //Set the position based on Player Pos
    //The Monster should be spawned at a point which is atleast at a distance
    //of MinDistance from the Player.
    const b2Vec2 & playerPos = m_pPlayer->getBody()->GetWorldCenter();
    b2Vec2 startPos(0.0f, 0.0f);

    bool posFound = false;
    while(posFound == false)
    {
        b2Vec2 pos( rand()% m_pMap->getWidth(), rand()%m_pMap->getHeight() );
        if( b2DistanceSquared( pos, playerPos ) >= MinDistance*MinDistance )
        {
            startPos = pos;
            posFound = true;
        }
    }

    //Get Data from XML File
    initFromXMLFile("data/monster", startPos );

    //Steering Behaviors
    m_pSB = std::auto_ptr<Neural_SB>(new Neural_SB(this, m_pBrain));
}

void Monster::update(float timeElapsed)
{
    /*
    b2Vec2 f1 = m_pSB->projectileAvoidance();
    b2Vec2 f2 = m_pSB->persuit();

    f1 *= timeElapsed;
    f2 *= timeElapsed;

    b2Vec2 f = f1 + f2;
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    vel += f;
    m_pBody->SetLinearVelocity(vel);

    */
    //const b2Vec2 & pos = m_pBody->GetWorldCenter();
    //std::cout << pos.x << " " << pos.y << std::endl;

    m_pSB->update(timeElapsed);

    /*
    if( rand() % 100 == 0 )
    {
        if(rand()%4)
            fireBullet();
        else
            fireShield();
    }*/

    m_fBulletTime -= timeElapsed;
    m_fShieldTime -= timeElapsed;
}

void Monster::render()
{
    render_Box2DEntity( m_pImage.get() , m_pBody );
}

bool Monster::fireBullet(const b2Vec2 & dir)
{
    if(m_fBulletTime > 0.0f)
        return false;

    //b2Vec2 dir = m_pBody->GetLinearVelocity();
    //dir.Normalize();

    //The bullets are fired a little ahead of the Monster so that they don't collide
    //with the Agent when they are fired.
    //Thye are fired 3/4 of image width ahead.
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos += (m_pImage->w *3.0/4 /World::ratio)*dir;

    //Create, init and add
    Bullet * b =  new Bullet( this, bullet_monster, pos, dir);
    b->init();
    m_pMap->addBullet(b);

    m_fBulletTime = m_fBulletDelay;
    return true;
}

bool Monster::fireShield(const b2Vec2 & dir)
{
    if(m_fShieldTime > 0.0f)
        return false;

    //The shield are also placed a little further (1.5 times the width)
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos += (m_pImage->w *1.5 /World::ratio)*dir;

    Shield * s = new Shield( this, shield_monster, pos, dir );
    s->init();
    m_pMap->addShield(s);

    m_fShieldTime = m_fShieldDelay;
    return true;
}

bool Monster::handleMessage(const Message & msg)
{
    return false;
}

void Monster::fireBullet()
{
    if( !canFireBullet() )
        return;

    const b2Vec2 & playerPos = m_pPlayer->getBody()->GetWorldCenter();
    const b2Vec2 dist = playerPos - m_pBody->GetWorldCenter();
    float lookAheadTime = dist.Length() /
                        (20.0 + m_pPlayer->getBody()->GetLinearVelocity().Length());

    if( dist.LengthSquared() >= 20*20 )
        return;

    b2Vec2 pos = m_pPlayer->getBody()->GetWorldCenter() + (lookAheadTime*m_pPlayer->getBody()->GetLinearVelocity());
    b2Vec2 dir = pos - m_pBody->GetWorldCenter();
    dir.Normalize();
    fireBullet(dir);
}


void Monster::fireShield()
{
    if( !canFireShield() )
        return;

    const b2Vec2 & playerPos = m_pPlayer->getBody()->GetWorldCenter();
    const b2Vec2 dist = playerPos - m_pBody->GetWorldCenter();

    if( dist.LengthSquared() >= 20*20 )
        return;

    float lookAheadTime = dist.Length() /
                        (15.0 + m_pPlayer->getBody()->GetLinearVelocity().Length());

    b2Vec2 pos = m_pPlayer->getBody()->GetWorldCenter() + (lookAheadTime*m_pPlayer->getBody()->GetLinearVelocity());
    b2Vec2 dir = pos - m_pBody->GetWorldCenter();
    dir.Normalize();

    fireShield(dir);
}


void Monster::deinit()
{
    m_pSB.reset();
    Box2DEntity::deinit();
}

void Monster::destructionAnim()
{
    //Get Position
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos *= World::ratio;

    //Create Effect
    Effect *e = new Effect(pos);
    e->getSprite().init("data/sprites/monster_explo");

    //Add to the Manager
    EffectManager::instance()->add(e);
}

void Monster::addStar() const
{
    if( (rand()%100) < 70 ) //70 % probability rate
    {
        Star * s = new Star(m_pMap->getWorld(), m_pBody->GetWorldCenter());
        s->init();
        m_pMap->addStar(s);
    }
}

