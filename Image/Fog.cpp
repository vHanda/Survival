#include "Fog.h"
#include "Plasma.h"
#include "GreyScale.h"
#include <iostream>


void Fog::operator()(SDL_Surface * s)
{
	//Create Layer Mask and fill it with Black
	SDL_PixelFormat * format = s->format;
	SDL_Surface * mask = SDL_CreateRGBSurface( SDL_HWSURFACE | SDL_SRCALPHA, s->w, s->h, 32,
						format->Rmask, format->Gmask, format->Bmask, format->Amask);
	SDL_FillRect( mask, NULL, 0 );


	//Create Clouds
	Plasma plasma_effect(m_lSeed , 1.0);
	plasma_effect(mask);

	GreyScale greyScale_effect;
	greyScale_effect(mask);

	//Apply Mask on Surface
	for(int i=0; i< s->w; i++)
		for(int j=0; j< s->h; j++)
		{
			Color sC;// = get_pixel(s, i, j);
			Color mC = get_pixel(mask, i, j);

			sC = m_Color;
			sC.a = mC.r;
			set_pixel(s, i, j, sC);
		}
}

