#include "Camera.h"
#include "World.h"
#include "Player.h"
Camera::Camera()
{
    //ctor
    m_Rect.x = m_Rect.y = 0;
    m_Rect.w = 800;
    m_Rect.h = 600;

    m_State = state_Normal;
    m_fVibrationTime = VibrationTime;
    m_fMaxVelocity = 0.5f;
    m_fPlayerLife = 0.0f;
}

Camera::~Camera()
{
    //dtor
}

void Camera::constructRect(b2Vec2 pos)
{
    pos *= World::ratio;

    int x = pos.x - m_Rect.w/2;
    int y = pos.y - m_Rect.h/2;

    m_Rect.x = x < 0 ? 0 : x > 800*3 ? 800*3 : x;
    m_Rect.y = y < 0 ? 0 : y > 600*3 ? 600*3 : y;
}

void Camera::update(float timeElapsed)
{
    //std::cout << "State : ";
    if(m_State == state_Normal)
    {
        //std::cout << " state_normal " << std::endl;
        constructRect(m_pPlayer->getBody()->GetWorldCenter());

        //State changes
        float life = m_pPlayer->getPercentLife();
        //std::cout << life << " " << m_fPlayerLife << std::endl;

        //Floating point comparison
        int prev = m_fPlayerLife * 100;
        int curr = life * 100;
        //std::cout << "Normal " << curr << " " << prev << std::endl;
        //bool result = (life - m_fPlayerLife) < 0.01;// && (life != m_fPlayerLife);
        //std::cout << "Normal - " << "Result : " << result << std::endl;
        if( curr - prev < 0 ) // life < m_fPlayerLife
        {
            //std::cout << "Changing state : " << curr << " " << prev << std::endl;
            //std::cout << "  " << result << std::endl;
            m_State = state_Vibrational;
            m_fVibrationTime = VibrationTime;
            m_Vel.x = (rand() % 2 ? -1 : 1)* m_fMaxVelocity;
            m_Vel.y = (rand() % 2 ? -1 : 1)* m_fMaxVelocity;
        }
        else
            m_fPlayerLife = life;
    }
    else if( m_State == state_Vibrational )
    {
        //std::cout << m_fVibrationTime << std::endl;
        m_fVibrationTime -= timeElapsed;
        b2Vec2 pos = m_pPlayer->getBody()->GetWorldCenter();
        pos += m_Vel;

        constructRect(pos);

        //Velocity Change
        m_Vel *= -1;

        //State Change
        if( m_fVibrationTime <= 0.0f)
        {
            m_State = state_Normal;
            m_fPlayerLife = m_pPlayer->getPercentLife();
            //std::cout << "Changing to Normal" << std::endl;
        }
    }
}

void Camera::set(Player * ent)
{
    assert(ent != 0);
    m_pPlayer = ent;
    m_fPlayerLife = m_pPlayer->getPercentLife();
}

void transform_Camera(SDL_Rect & rect)
{
    Camera * camera = Camera::getInstance();
    const SDL_Rect & m_Rect = camera->getRect();

    rect.x -= m_Rect.x;
    rect.y -= m_Rect.y;
}

void transform_Camera(b2Vec2 & vec)
{
    Camera * camera = Camera::getInstance();
    const SDL_Rect & m_Rect = camera->getRect();

    vec.x -= m_Rect.x;
    vec.y -= m_Rect.y;
}

