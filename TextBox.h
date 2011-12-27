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

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Image/SDL_SurfacePtr.h"
//#include <SDL/SDL_gfxPrimitives.h>
#include "Engine/Keyboard.h"
#include <string>
#include <SDL/SDL_ttf.h>

class TextBox
{
private :
    SDL_SurfacePtr m_pTextImage;

    std::string m_sText;
    TTF_Font * m_pFont;

    SDL_Rect m_Pos;
    SDL_Color m_Color;

    bool m_bDone;

    int m_iTimes;
    SDLKey m_LastKey;
public:
    TextBox();
    virtual ~TextBox();

    void setPos(int x, int y)
    { m_Pos.x = x; m_Pos.y = y; }

    void update(float timeElapsed);
    void render();

    bool done() const { return m_bDone; }
    std::string get() const { return m_sText; }
};

#endif // TEXTBOX_H
