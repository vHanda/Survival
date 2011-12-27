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

