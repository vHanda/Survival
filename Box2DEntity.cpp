#include "Box2DEntity.h"
#include <SDL/SDL_rotozoom.h>
#include <cmath>
#include "World.h"

void Box2DEntity::adjustAngle(SDL_SurfacePtr & s)
{
    b2Vec2 vel = m_pBody->GetLinearVelocity();
    if( vel == b2Vec2(0.0f, 0.0f) )
        return;

    vel.Normalize();
    const b2Vec2 up(0.0f, -1.0f);

    float dot = b2Dot( vel, up );
    float angle = acos(dot); //In Radians
    angle *= 180.0/b2_pi;
    if( vel.x > 0 )
        angle *= -1; //This is becuase the x-axis is being ignored in up

    float diff = angle - m_fAngle;
    if(diff == 0)
        return;

    if( abs(diff) < m_fMinAngle )
        return;

    //Rotate
    SDL_Surface * newSurface = rotozoomSurface( s.get(), diff, 1.0f, 10 );
    s = newSurface;
    m_fAngle += diff;

    //std::cout << "Vel : " << vel.x << " " << vel.y << std::endl;
    //std::cout << "\t" << angle << std::endl;
    //std::cout << diff << std::endl << std::endl;
}

void Box2DEntity::deinit()
{
    if(m_pBody != NULL)
    {
        //std::cout << "Deinit" << std::endl;
        m_pWorld->DestroyBody(m_pBody);
        m_pBody = NULL;
    }
}
