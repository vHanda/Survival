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
