#include "Sprite.h"
#include <SDL/SDL_rotozoom.h>
Sprite::Sprite(std::string fileName, int fps)
: m_iFPS(fps)
{
    //ctor
    m_iFrameNo = 0;
    m_fDelay = 1.00/m_iFPS;
    m_fTotalTime = 0.0f;
    m_bDone = false;
    m_PlayType = play_once;

    if(fileName != "")
        init(fileName);
}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::render(const b2Vec2 & pos)
{
    if( m_Sprites.empty() )
        return;

    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_Surface * image = m_Sprites[m_iFrameNo].get();

    SDL_Rect rect;
	rect.x = pos.x - image->w/2;
	rect.y = pos.y - image->h/2;

    SDL_BlitSurface( image , NULL, screen, &rect);
}

void Sprite::update(float timeElapsed)
{
    if(m_PlayType == play_loop)
        m_bDone = false;

    if(m_bDone == true || m_PlayType == play_dont)
        return;

    m_fTotalTime += timeElapsed;

    if(m_fTotalTime >= m_fDelay)
    {
        m_iFrameNo += (int)1;//m_fTotalTime/delay;
        if(m_iFrameNo >= m_Sprites.size())
        {
            if(m_PlayType != play_once)
                m_iFrameNo = 0;
            else
                m_iFrameNo = m_Sprites.size() - 1;
            m_bDone = true;
        }
        m_fTotalTime = 0.00f;
    }
}

void Sprite::init(std::string fileName)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();
    TiXmlElement * pElement = doc.RootElement();
    init(pElement);
}

//TODO: Optimize this ..
void Sprite::init(TiXmlElement * pElement)
{
    if(pElement->ValueStr() != "sprite")
        return;

    TiXmlAttribute * pAtt = pElement->FirstAttribute();
    setFPS( pAtt->IntValue() );

    TiXmlElement * pChild = pElement->FirstChildElement();
    while(pChild != NULL)
    {
        if(pChild->ValueStr() != "surface")
            continue;

        std::string fileName = pChild->GetText();
        SDL_SurfacePtr pSurface = load_image(fileName);
        float zoom = 1.0f;
        float rot = 0.0f;
        float alpha = 1.0;

        TiXmlAttribute * pAttrib = pChild->FirstAttribute();
        if(pAttrib != NULL)
        {
            SDL_Rect rect = {-1,-1,-1,-1};
            while(pAttrib != NULL)
            {
                //std::cout << pAttrib->Name() << std::endl;
                if(pAttrib->Name() == std::string("x"))
                    rect.x = pAttrib->IntValue();
                else if(pAttrib->Name() == std::string("y"))
                    rect.y = pAttrib->IntValue();
                else if(pAttrib->Name() == std::string("w"))
                    rect.w = pAttrib->IntValue();
                else if(pAttrib->Name() == std::string("h"))
                    rect.h = pAttrib->IntValue();
                else if(pAttrib->Name() == std::string("rot"))
                    rot = pAttrib->DoubleValue();
                else if(pAttrib->Name() == std::string("zoom"))
                    zoom = pAttrib->DoubleValue();
                else if(pAttrib->Name() == std::string("alpha"))
                    alpha = pAttrib->DoubleValue();

                pAttrib = pAttrib->Next();
            }
            if( rect.x != -1 && rect.y != -1 && rect.w != -1 && rect.h != -1)
                pSurface = getSurface( pSurface.get(), rect );
            if( zoom != 1.0 || rot != 0.0f )
                pSurface = rotozoomSurface( pSurface.get(), rot, zoom, 1); //1 is for smoothing
            if( alpha != 1.0 )
            {
                int a = 255*alpha;
                SDL_SetAlpha( pSurface.get(), SDL_SRCALPHA|SDL_RLEACCEL, a);
            }
        }

        m_Sprites.push_back( new SDL_SurfacePtr(pSurface) );
        pChild = pChild->NextSiblingElement();
    }
}

void Sprite::setFPS(int fps)
{
    m_iFPS = fps;
    m_fDelay = 0.0f;

    if( m_iFPS != 0 )
        m_fDelay = 1.00/m_iFPS;
}

void Sprite::zoom(float ratio)
{
    if(ratio == 1.0)
        return;

    int size = m_Sprites.size();
    for(unsigned int i=0; i<size; i++)
    {
        SDL_Surface * sur = rotozoomSurface(m_Sprites[i].get(), 0, ratio, 0);
        m_Sprites.push_back( new SDL_SurfacePtr(sur) );
    }
    m_Sprites.erase( m_Sprites.begin(), m_Sprites.begin() + size );
}
