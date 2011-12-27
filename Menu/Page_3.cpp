#include "Page_3.h"

Page_3::Page_3()
{
    m_pImage = load_image("data/gfx/menu/page_3.png");
    m_pPlayer = load_image("data/gfx/player/player.png");
    m_pBulletImage = load_image("data/gfx/bullet/bullet.png");
    m_Pos.x = 100;
    m_Pos.y = 400;
    m_State = state_right;
    m_fBulletDelay = 0.15;
}

Page_3::~Page_3()
{

}

void Page_3::update(float timeElapsed)
{
    switch( m_State )
    {
    case state_left :
        m_Pos.x -= 5;
        break;
    case state_right :
        m_Pos.x += 5;
        break;
    }

    if( m_Pos.x < 250 )
        m_State = state_right;
    if( m_Pos.x > 550 )
        m_State = state_left;

    //Add Bullets
    if(m_fBulletDelay <= 0.0f)
    {
        //if(rand() % 2)
        //{
            Bullet b;
            b.pos = m_Pos;
            b.vel.x = 9;
            b.vel.y = 9;

            if( rand() % 2 ) b.vel.x *= -1;
            if( rand() % 2 ) b.vel.y *= -1;

            m_List.push_back(b);
        //}
        m_fBulletDelay = 0.15;
    }

    //Adjuct Bullet Pos
    for(unsigned int i=0; i<m_List.size(); i++)
    {
        m_List[i].pos.x += m_List[i].vel.x;
        m_List[i].pos.y += m_List[i].vel.y;

        if(m_List[i].pos.x <= 5 || m_List[i].pos.y <= 5)
        {
            m_List[i].pos.x = m_List[i].pos.y = 1000;
            m_List[i].vel = b2Vec2(0.0f, 0.0f);
        }
    }

    m_fBulletDelay -= timeElapsed;
}

void Page_3::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    SDL_BlitSurface( m_pPlayer.get(), NULL, screen, &m_Pos);
    for(unsigned int i=0; i<m_List.size(); i++)
    {
        SDL_BlitSurface( m_pBulletImage.get(), NULL, screen, &m_List[i].pos);
    }
}
