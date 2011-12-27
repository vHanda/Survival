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

#include "Mouse.h"
#include <iostream>

int Mouse::xpos;
int Mouse::ypos;
bool Mouse::button[4];

Mouse::Mouse()
{
	xpos = 0;
	ypos = 0;
	button[0] = false;
	button[1] = false;
	button[2] = false;
	button[3] = false;
}

void Mouse::onMouseMotion(int x, int y, int state, int xrel, int yrel)
{
	xpos = x;
	ypos = y;
	//button = state;
}
void Mouse::onMouseDown(int x, int y, int _button)
{
	xpos = x;
	ypos = y;
	button[ _button ] = true;
}

void Mouse::onMouseUp(int x, int y, int _button)
{
	xpos = x;
	ypos = y;
	button[ _button ] = false;
}


bool Mouse::doubleClick(float timeElapsed)
{
    static bool singleClick = false;
    static float timer = 0.00f;
    static float dblClickGap = 0.05f;

    if( isDown( 1 ) == true )
    {
        //std::cout << "\t" << timer << std::endl;
        if(singleClick == false)
        {
            //std::cout << "Single Click .. started" << std::endl;
            singleClick = true;
            timer = 0.00f;
            return false;
        }
        else
        {
            if(timer >= dblClickGap && timer <= dblClickGap*4)
            {
                //std::cout << "Timer : " << timer << std::endl;
                singleClick = false;
                return true;
            }

            //std::cout << "Leave the mouse button !!" << std::endl;
        }
    }
    else
    {
        //std::cout << "Time Elapsed.. " << std::endl;
        timer += timeElapsed;

        if( timer > dblClickGap*4 )
        {
            //std::cout << "Reseting .." << std::endl;
            singleClick = false;
        }
        return false;
    }
    return false;
}
