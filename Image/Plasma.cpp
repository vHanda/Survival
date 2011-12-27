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

#include "Plasma.h"
#include <iostream>

void Plasma::operator ()(SDL_Surface * s)
{
	m_pSurface = s;
	
	int x1 = 0;
	int y1 = 0;
	int x2 = s->w -1;
	int y2 = s->h -1;
	
	SDL_LockSurface( s );
	if( x1 != x2 && y1 != y2 )
	{
		do_plasma( x1, y1, x2, y2, -1, 0 );
		
		int depth = 1;
		int scale_depth = 1;
		
		while( do_plasma( x1, y1, x2, y2, depth, scale_depth ) == false )
		{
			depth++;
		}
	}
	SDL_UnlockSurface( s );
}

bool Plasma::do_plasma(int x1, int y1, int x2, int y2, int depth, int scale_depth)
{
	Color tl, ml, bl, tm, mm, bm, tr, mr, br;
	
	int xm = ( x1 + x2 )/ 2;
	int ym = ( y1 + y2 )/ 2;
	
	if(depth == -1)
	{
		random_rbg(tl);
		random_rbg(ml);
		random_rbg(bl);
		random_rbg(tm);
		random_rbg(mm);
		random_rbg(bm);
		random_rbg(tr);
		random_rbg(mr);
		random_rbg(br);
		
		set_pixel(m_pSurface, x1, y1, tl);
		set_pixel(m_pSurface, x1, ym, ml);
		set_pixel(m_pSurface, x1, y2, bl);
		set_pixel(m_pSurface, xm, y1, tm);
		set_pixel(m_pSurface, xm, ym, mm);
		set_pixel(m_pSurface, xm, y2, bm);
		set_pixel(m_pSurface, x2, y1, tr);
		set_pixel(m_pSurface, x2, ym, mr);
		set_pixel(m_pSurface, x2, y2, br);
		
		return false;
	}
	
	if(depth == 0)
	{
		if(x1 == x2 && y1 == y2)
			return false;
		
		get_pixel(m_pSurface, x1, y1, tl);
		get_pixel(m_pSurface, x1, y2, bl);
		get_pixel(m_pSurface, x2, y1, tr);
		get_pixel(m_pSurface, x2, y2, br);
		
		
		int ran = (int)((256.0 / (2 * scale_depth)) * m_fTurbulance);
		if (xm != x1 || xm != x2)
		{
			// Left
			ml = average_color(tl, bl);
			add_random(ml, ran);
			set_pixel(m_pSurface, x1, ym, ml);

			if (x1 != x2)
			{
				// Right 
				mr  = average_color(tr, br);
				add_random(mr, ran);
				set_pixel(m_pSurface, x2, ym, mr);
			}
		}

		if (ym != y1 || ym != y2)
		{
			if (x1 != xm || ym != y2)
			{
				// Bottom
				Color mb  = average_color(bl, br);
				add_random(mb, ran);
				set_pixel(m_pSurface, xm, y2, mb);
			}

			if (y1 != y2)
			{
				// Top
				Color mt  = average_color(tl, tr);
				add_random(mt, ran);
				set_pixel(m_pSurface, xm, y1, mt);
			}
		}

		if (y1 != y2 || x1 != x2)
		{
			// Middle pixel
			Color tmp;
			mm  = average_color(tl, br);
			tmp = average_color(bl, tr);
			mm  = average_color(mm, tmp);

			add_random(mm, ran);
			set_pixel(m_pSurface, xm, ym, mm);
		}
		
		return x2 - x1 < 3 && y2 - y1 < 3;
	} //depth == 0
	
	if (x1 < x2 || y1 < y2)
	{
		// Top left.
		do_plasma (x1, y1, xm, ym, depth - 1, scale_depth + 1);
		/* Bottom left. */
		do_plasma (x1, ym, xm, y2, depth - 1, scale_depth + 1);
		/* Top right. */
		do_plasma (xm, y1, x2, ym, depth - 1, scale_depth + 1);
		/* Bottom right. */
		return do_plasma (xm, ym, x2, y2, depth - 1, scale_depth + 1);
	}
	
	return true;	
}

