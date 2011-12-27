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

#include "../Engine/ErrorHandler.h"
#include "SDL_SurfacePtr.h"
#include <cassert>

SDL_SurfacePtr::SDL_SurfacePtr()
: ptr(NULL)
{}

SDL_SurfacePtr::SDL_SurfacePtr(SDL_Surface * surface)
: ptr(surface)
{}

SDL_SurfacePtr::SDL_SurfacePtr(const SDL_SurfacePtr & rhs)
{
    ptr = NULL;
    *this = rhs;
}

SDL_SurfacePtr::~SDL_SurfacePtr()
{
	SDL_FreeSurface( ptr );
}

bool operator ==(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs)
{ return lhs.get() == rhs.get(); }
bool operator !=(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs)
{ return lhs.get() != rhs.get(); }

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    if(loadedImage == NULL)
        G_THROW(filename + " couldn't be loaded");

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        //assert(optimizedImage);
        if(optimizedImage == NULL)
            G_THROW("ImageFile " + filename + " couldn't be converted");
        //Free the old surface
        SDL_FreeSurface( loadedImage );

    }

    //Return the optimized surface
    return optimizedImage;
}
