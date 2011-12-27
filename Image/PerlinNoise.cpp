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

#include "PerlinNoise.h"
#include <cmath>
#include <iostream>
#include <iomanip>

PerlinNoise::PerlinNoise(int oct, float per, float zoom, int start)
: m_iOctaves(oct), m_fPersistance(per), m_fZoom(zoom)
{
    m_Primes.reserve(oct+1);
    m_Primes.push_back( nextPrime(start) );

    for(int i=1; i<oct+1; i++)
        m_Primes.push_back( nextPrime(m_Primes[i-1]) );

    std::cout << oct << std::endl << std::setprecision(5) << per << std::endl << zoom << std::endl
    << start << std::endl << std::endl;
}

PerlinNoise::~PerlinNoise()
{
}

float PerlinNoise::Noise(int x, int y, int i)
{
    long n = x + y * 57;
    n = (n<<13) ^ n;
    //1376312589
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + m_Primes[i]) & 0x7fffffff) /(m_Primes[i+1]*1.0));
}

float PerlinNoise::SmoothNoise(int x, int y, int i)
{
    float corners = ( Noise(x-1, y-1,i)+Noise(x+1, y-1,i)+Noise(x-1, y+1,i)+Noise(x+1, y+1,i) ) / 16;
    float sides   = ( Noise(x-1, y,i)  +Noise(x+1, y,i)  +Noise(x, y-1,i)  +Noise(x, y+1,i) ) /  8;
    float center  =  Noise(x, y,i) / 4;
    return corners + sides + center;
}

float PerlinNoise::InterpolatedNoise(float x, float y, int i)
{
    int integerX = (int)x;
    float fractionalX = x - integerX;

    int integerY = (int)y;
    float fractionalY = y - integerY;

    float v1 = SmoothNoise(integerX,     integerY,i);
    float v2 = SmoothNoise(integerX + 1, integerY,i);
    float v3 = SmoothNoise(integerX,     integerY + 1,i);
    float v4 = SmoothNoise(integerX + 1, integerY + 1,i);

    float i1 = Interpolate(v1 , v2 , fractionalX);
    float i2 = Interpolate(v3 , v4 , fractionalX);

    return Interpolate(i1 , i2 , fractionalY);
}


float PerlinNoise::Interpolate(float a, float b, float num)
{
    float ft = num * 3.1415927;
	float f = (1 - cos(ft)) * .5;

	return  a*(1-f) + b*f;
}

float PerlinNoise::Perlin(float x, float y)
{
    float total = 0;
    for(int i=0; i<m_iOctaves; i++)
    {
        float freq = pow(2, i);
        float amp = pow(m_fPersistance, i);

        total += InterpolatedNoise(x*freq/m_fZoom, y*freq/m_fZoom, i) * amp;
    }
    return total;
}

void PerlinNoise::operator()(SDL_Surface * s)
{
    SDL_FillRect(s, NULL, 0);

    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    for(int x=0; x<s->w; x++)
        for(int y=0; y<s->h; y++)
        {
            float t = Perlin( (int)x, (int)y );
            int value = 128 + 128*t;
            clamp(0, value, 255);
            //std::cout << value << std::endl;

            Color c;
            c.r = r;
            c.g = g;
            c.b = b;
            c.a = value;

            set_pixel(s, x, y, c);
        }

}

bool PerlinNoise::isPrime(int x)
{
    int sq = sqrt(x);
    for(int i=2; i<sq; i++)
    {
        if( x % i == 0 )
            return true;
    }
    return false;
}

int PerlinNoise::nextPrime(int x)
{
    for(int i=x+1; ; i++)
        if(isPrime(i))
            return i;
}
