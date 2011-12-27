#ifndef _IMAGEEFFECT_
#define _IMAGEEFFECT_

#include "Color.h"

class ImageEffect {
public :
	ImageEffect() {}
	virtual ~ImageEffect() {}
	virtual void operator()(SDL_Surface * s) = 0;
};

#endif
