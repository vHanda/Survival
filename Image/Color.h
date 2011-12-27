#ifndef _COLOR_
#define _COLOR_

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cassert>

template<typename T>
inline T clamp(const T & lower, const T & value, const T & upper)
{
	return value > upper ? upper : (value < lower ? lower : value);
}

class Color {
public :
	Uint8 r,g,b,a;

	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a = 255)
	: r(_r), g(_g), b(_b), a(_a) {}

	Color(Uint8 value)
	: r(value), g(value), b(value), a(value) {}

	Color()
	: r(0), g(0), b(0), a(0) {}

	inline Color operator +(const Color & c) const;
	inline Color operator -(const Color & c) const;
	inline Color operator /(Uint8 f) const;
	inline const Color & operator +=(const Color & c);
	inline const Color & operator -=(const Color & c);
	inline int to_int(SDL_PixelFormat * format = SDL_GetVideoSurface()->format) const;

};

inline Color Color::operator +(const Color & c) const
{
	int nr = (int)r + c.r;
	int nb = (int)b + c.b;
	int ng = (int)g + c.g;
	int na = (int)a + c.a;

	return Color( 	clamp(0, nr, 255),
					clamp(0, nb, 255),
					clamp(0, ng, 255),
					clamp(0, na, 255) );
}

inline Color Color::operator -(const Color & c) const
{
	int nr = (int)r - c.r;
	int nb = (int)b - c.b;
	int ng = (int)g - c.g;
	int na = (int)a - c.a;

	return Color( 	clamp(0, nr, 255),
					clamp(0, nb, 255),
					clamp(0, ng, 255),
					clamp(0, na, 255) );
}

inline Color Color::operator /(Uint8 f) const
{
	return Color((Uint8)r/f, (Uint8)b/f, (Uint8)g/f, (Uint8)a/f);
}

inline const Color & Color::operator +=(const Color & c)
{
	*this = (*this)+c;
	return *this;
}

inline const Color & Color::operator -=(const Color & c)
{
	*this = (*this)-c;
	return *this;
}

inline int Color::to_int(SDL_PixelFormat * format) const
{
	return SDL_MapRGBA(format, r, g, b, a);
}


inline Color average_color(const Color & c1, const Color & c2)
{
	return Color( 	c1.r/2 + c2.r/2,
					c1.g/2 + c2.g/2,
					c1.b/2 + c2.b/2,
					c1.a/2 + c2.a/2 	);
}

inline void set_pixel(SDL_Surface *s, int x, int y, const Color & c)
{
	pixelRGBA(s, x, y, c.r , c.g, c.b, c.a);
}

inline Color get_pixel(SDL_Surface *s, int x, int y)
{
	if(x < 0 || y<0 || x>= s->w || y >=s->h)
		return Color(0);

	assert( s != NULL && "GetPixel : SDL_Surface = NULL" && __LINE__&&__FILE__);

	SDL_LockSurface(s);
		SDL_PixelFormat * format = s->format;
		int bpp = format->BytesPerPixel;

		Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * bpp;
		Uint32 clr = *(Uint32 *)p;

		Color c;
		SDL_GetRGBA(clr, format, &c.r, &c.g, &c.b, &c.a);
	SDL_UnlockSurface(s);
	return c;
}

inline void get_pixel(SDL_Surface *s, int x, int y, Color & c)
{
	c = get_pixel(s,x,y);
}

#endif
