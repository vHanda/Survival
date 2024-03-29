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

#ifndef HELP_H
#define HELP_H

#include "../FSM/StateMachine.h"
#include "../Image/SDL_SurfacePtr.h"
#include <string>
#include <vector>
#include <SDL/SDL_ttf.h>
#include "Page.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <Box2D/Box2D.h>

class App;

class Help : public State<App>
{
private :
    boost::ptr_vector<Page> m_Pages;
    int m_iPageNum;

    SDL_SurfacePtr m_pLeftArrow;
    SDL_SurfacePtr m_pRightArrow;
    SDL_SurfacePtr m_pPageNum;
    TTF_Font * m_pFont;

    void renderPageNum();
public :
    Help();
    ~Help();

    void enter(App * a);
    void update(App * a, float timeElapsed);
    void render(App * a);
    void exit(App * a);
    bool handleMessage(App * a, const Message & m) { return false;}
};

//Collision Tests
inline bool ct_Rect_Point(const b2Vec2 & tl, const b2Vec2 & br, const b2Vec2 & p)
{
	if( p.x < tl.x ) return 0;
	if( p.x > br.x ) return 0;
	if( p.y < tl.y ) return 0;
	if( p.y > br.y ) return 0;
	return true;
}

inline bool ct_Rect_Point(const SDL_Rect & rect, const b2Vec2 & p)
{
    b2Vec2 tl( rect.x, rect.y );
    b2Vec2 br( tl.x + rect.w, tl.y + rect.h );
    return ct_Rect_Point(tl, br, p);
}
#endif // HELP_H
