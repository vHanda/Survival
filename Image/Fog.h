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

