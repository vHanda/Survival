#ifndef _FOG_
#define _FOG_

#include "ImageEffect.h"

class Fog : public ImageEffect {
private :
	Color m_Color;
	float m_fTurbulance;
	unsigned long m_lSeed;
public :
	Fog(const Color & c, float t, unsigned long seed = SDL_GetTicks() )  
	: m_Color(c), m_fTurbulance(t), m_lSeed(seed) {}
	~Fog() {}
	
	virtual void operator()(SDL_Surface * s);
};

#endif

