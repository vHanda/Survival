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

#include "Player.h"
#include "World.h"
#include "Engine/Engine.h"
#include "Map.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Bullet.h"
#include "Shield.h"
#include "Star.h"
#include "tinyxml/tinyxml.h"
#include <SDL/SDL_rotozoom.h>

Player::Player(Map *map)
: Agent(map)
{

}

Player::~Player()
{
    //deinit();
}

void Player::init()
{
    b2Vec2 startPos( rand()% m_pMap->getWidth(), rand()%m_pMap->getHeight() );
    initFromXMLFile("data/player", startPos);
    m_fMaxLife = 50.0f;
    m_iMonstersKilled = 0;

    //Sprite
    m_Sprite.init("data/sprites/player_sprite");
}

void Player::update(float timeElapsed)
{
    //Controlls
    b2Vec2 vel(0.00f, 0.00f);
    if(gKB->isDown( SDLK_a ) || gKB->isDown( SDLK_LEFT ) )
        vel -= b2Vec2(m_fSpeed, 0);
    if(gKB->isDown( SDLK_d ) || gKB->isDown( SDLK_RIGHT ) )
        vel += b2Vec2(m_fSpeed, 0);

    if(gKB->isDown( SDLK_w ) || gKB->isDown( SDLK_UP ) )
        vel -= b2Vec2( 0, m_fSpeed );
    if(gKB->isDown( SDLK_s) || gKB->isDown( SDLK_DOWN ) )
        vel += b2Vec2( 0, m_fSpeed );

    if(vel.LengthSquared() > m_fSpeed*m_fSpeed)
    {
        vel.Normalize();
        vel *= m_fSpeed;
    }
    //b2Vec2 force = vel;
    //force *= m_pBody->GetMass();
    m_pBody->SetLinearVelocity( vel );
    //m_pBody->ApplyForce(force, b2Vec2(0.0f, 0.0f));

    //Shooting
    if(Mouse::getInstance()->isDown( 1 ) && m_fBulletTime <= 0.0f)
    {
        fireBullet();
        m_fBulletTime = m_fBulletDelay;
    }
    if(Mouse::getInstance()->isDown( 3 ) && m_fShieldTime <= 0.0f)
    {
        fireShield();
        m_fShieldTime = m_fShieldDelay;
    }

    m_fBulletTime -= timeElapsed;
    m_fShieldTime -= timeElapsed;

}

void Player::render()
{
    //adjustAngle(m_pImage);
    int frame = (m_fLife / 10) * 2.5 ;
    if( frame < 0 ) frame = 0;
    if( frame >= 9) frame = 9;

    render_Box2DEntity( m_Sprite[frame].get() , m_pBody );
    //render_Box2DEntity( m_pImage.get(), m_pBody );
}

bool Player::handleMessage(const Message & msg)
{
    return false;
}

void Player::fireBullet()
{
    b2Vec2 dir = getCursorWorldCoords();
    dir -= m_pBody->GetWorldCenter();
    dir.Normalize();

    //The bullets are fired a little ahead of the player so that they don't collide
    //with the player when they are fired.
    //Thye are fired 3/4 of image width ahead.
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos += (m_pImage->w *3.0/4 /World::ratio)*dir;

    //Create, init and add
    Bullet * b =  new Bullet( this, bullet_player, pos, dir);
    b->init();
    m_pMap->addBullet(b);
}

void Player::fireShield()
{
    b2Vec2 dir = getCursorWorldCoords();
    dir -= m_pBody->GetWorldCenter();
    dir.Normalize();

    //The shield are also placed a little further (1.5 times the width)
    b2Vec2 pos = m_pBody->GetWorldCenter();
    pos += (m_pImage->w *1.5 /World::ratio)*dir;

    Shield * s = new Shield( this, shield_player, pos, dir );
    s->init();
    m_pMap->addShield(s);
}
