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

#ifndef _SDL_SURFACE_PTR_
#define _SDL_SURFACE_PTR_

#include <SDL/SDL.h>
#include <string>
#include <SDL/SDL_image.h>
#include <cassert>


//Surface Creation
inline SDL_Surface * SDL_CreateRGBSurface(Uint32 flags, int width, int height,
        SDL_Surface * type)
{
    return SDL_CreateRGBSurface( flags, width, height, type->format->BitsPerPixel,
            type->format->Rmask, type->format->Gmask, type->format->Bmask, type->format->Amask );
}

inline SDL_Surface * SDL_CreateRGBSurface(int width, int height, SDL_Surface * type)
{
    return SDL_CreateRGBSurface( type->flags, width, height, type );
}

inline SDL_Surface * SDL_CreateRGBSurface(int width, int height)
{
    return SDL_CreateRGBSurface( width, height, SDL_GetVideoSurface() );
}
////////////////////


class SDL_SurfacePtr {
	SDL_Surface * ptr;
public :
	SDL_SurfacePtr();
	SDL_SurfacePtr(SDL_Surface * surface);
	SDL_SurfacePtr(const SDL_SurfacePtr & rhs);

	~SDL_SurfacePtr();

	SDL_Surface* get() const { return ptr; }
	SDL_Surface* release() { SDL_Surface *p = ptr; ptr = NULL; return p; }
	void reset() { SDL_FreeSurface(ptr); ptr = NULL; }
	SDL_Surface* operator ->() const { return ptr; }
	SDL_Surface& operator  *() const { return *ptr;}

	const SDL_SurfacePtr & operator =(SDL_Surface* rhs)
	{
	    if(ptr)
            SDL_FreeSurface(ptr);
        ptr = rhs;
        return *this;
    }

	SDL_SurfacePtr & operator =(const SDL_SurfacePtr & rhs)
	{
		if( ptr != NULL)
			SDL_FreeSurface( ptr );

        SDL_Surface * pRhs = rhs.get();
        pRhs->flags &= ! SDL_SRCALPHA;
		ptr = SDL_CreateRGBSurface(rhs->w, rhs->h, rhs.get());
        SDL_BlitSurface( rhs.get(), NULL, ptr, NULL );
		pRhs->flags |= SDL_SRCALPHA;
		return *this;
	}

};

bool operator ==(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs);
bool operator !=(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs);

SDL_Surface *load_image( std::string filename ) ;

inline SDL_Surface * getSurface(SDL_Surface * surface, SDL_Rect & rect)
{
    //Creating the new surface
    SDL_Surface * newSurface;
    newSurface = SDL_CreateRGBSurface( rect.w , rect.h, surface );
    assert(newSurface != NULL);

    //Filling to new surface with Black
    SDL_FillRect(newSurface, NULL, 0x00000000);

    //This is done because of the way SDL_BlitSurface Workds
    surface->flags &= !SDL_SRCALPHA;
    SDL_BlitSurface( surface, &rect, newSurface, NULL);
    surface->flags |= SDL_SRCALPHA;

    return newSurface;
}

#endif
