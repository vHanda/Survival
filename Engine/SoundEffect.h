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

#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL/SDL_mixer.h>
#include <string>

class SoundEffect
{
public:
    SoundEffect(Mix_Chunk * chunk = NULL);
    SoundEffect(std::string fileName);
    virtual ~SoundEffect();

    void play(int loops = 0);
    bool done();
    void assign(Mix_Chunk * chunk)
    { if(!m_Sound) m_Sound = chunk; }
    void init(std::string fileName);

    Mix_Chunk* getChunk() { return m_Sound; }
protected:

private:
    Mix_Chunk * m_Sound;
    int m_iChannelNo;
};

#endif // SOUNDEFFECT_H
