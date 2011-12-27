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

#include "Page_5.h"

Page_5::Page_5()
{
    m_pImage = load_image("data/gfx/menu/page_5.png");
    m_Sprite.init("data/sprites/player_sprite");
    m_Sprite.setFPS( 3 );
    m_Sprite.setPlayType( Sprite::play_loop );
}

Page_5::~Page_5()
{
}

void Page_5::update(float timeElapsed)
{
    m_Sprite.update(timeElapsed);
}

void Page_5::render()
{
    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_BlitSurface( m_pImage.get(), NULL, screen, NULL );

    m_Sprite.render( b2Vec2( 210, 275 ) );
}
