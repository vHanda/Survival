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

#ifndef _GREY_SCALE_
#define _GREY_SCALE_

#include "ImageEffect.h"

class GreyScale : public ImageEffect {
private :

public :
	GreyScale() {}
	~GreyScale() {}

	inline virtual void operator()(SDL_Surface * s);
};

void GreyScale::operator()(SDL_Surface * s)
{
	for(int i=0; i< s->w ; i++)
	{
		for(int j=0; j<s->h; j++)
		{
			Color c = get_pixel(s, i, j);
			//int luma = (int)(c.r*0.3 + c.g*0.59+ c.b*0.11);
			int luma = (static_cast<int>(c.r) + c.g + c.b)/3;
			c.r = c.g = c.b = luma;
			set_pixel(s, i, j, c);
		}
	}
}

#endif
