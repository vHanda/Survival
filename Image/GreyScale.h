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
