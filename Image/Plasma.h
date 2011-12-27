#ifndef _PLASMA_
#define _PLASMA_

#include "ImageEffect.h"
#include "Rand/VRandom.h"

class Plasma : public ImageEffect {
private :
	SDL_Surface * m_pSurface;

	VRandom m_Random;
	float m_fTurbulance;
	bool m_bAlpha;

	inline void add_random(Color & c, int amount);
	inline void random_rbg(Color & c);

	bool do_plasma(int x1, int y1, int x2, int y2, int depth, int scale_depth);
public :
	Plasma(unsigned long seed, float turbulance = 1.00, bool has_alpha = false)
	:	m_Random(seed), m_fTurbulance(turbulance), m_bAlpha(has_alpha) {}
	virtual ~Plasma() {}

	void setTurbulance(float t) { m_fTurbulance = t; }
	void setSeed(unsigned long s) { m_Random.seed(s); }
	void operator ()(SDL_Surface * s);
};

void Plasma::add_random(Color & c, int amount)
{
	amount /= 2;
	if(amount > 0)
	{
		int temp;
		temp = c.r + m_Random.range( -amount, amount);
		c.r = clamp(0, temp, 255);

		temp = c.g + m_Random.range( -amount, amount);
		c.g = clamp(0, temp, 255);

		temp = c.b + m_Random.range( -amount, amount);
		c.b = clamp(0, temp, 255);

		if( m_bAlpha )
		{
			temp = c.a + m_Random.range( -amount, amount);
			c.a = clamp(0, temp, 255);
		}
	}
}

void Plasma::random_rbg(Color & c)
{
	c.r = m_Random() % 256;
	c.g = m_Random() % 256;
	c.b = m_Random() % 256;

	if( m_bAlpha )
		c.a = m_Random() % 256;
	else
		c.a = 255;
}
#endif
