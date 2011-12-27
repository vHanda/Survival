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

#ifndef _MOUSE_
#define _MOUSE_

#define SDL_LMOUSE
#define SDL_RMOUSE

class Mouse {
	static int xpos,ypos;
	static bool button[4];
public :
	Mouse();
	~Mouse() {}

	void onMouseMotion(int x, int y, int state, int xrel, int yrel);
	void onMouseDown(int x, int y, int _button);
	void onMouseUp(int x, int y, int _button);

	void getPos(int &x, int &y) const
	{ x = xpos; y = ypos; }
	bool isDown(int b) const
	{ return button[b]; }

	static Mouse * getInstance() { static Mouse m; return &m; }
	bool doubleClick(float timeElapsed);
};

#define gMOUSE Mouse::getInstance()

#endif
