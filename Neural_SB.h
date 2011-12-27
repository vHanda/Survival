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

#ifndef NEURAL_SB_H
#define NEURAL_SB_H

#include "Monster_SB.h"
#include "NeuralNetwork/NN_File.h"
#include <vector>

class Neural_SB : public Monster_SB
{
private :
    NN_File * m_pBrain;
    float m_fMaxForce;

    enum input {
        i_life = 0,
        i_plr_dist,
        i_plr_life,
        i_killed
    };
    std::vector<float> m_Input;

    enum output {
        o_persuit =0,
        o_evade,
        o_flocking,
        o_fire_bullet,
        o_fire_shield
    };
    std::vector<float> m_Output;

    void getInput();
    b2Vec2 getForce();
    bool accumForce(b2Vec2 & totForce, b2Vec2 force) const;
public:
    Neural_SB(Monster * m, NN_File * pBrain);
    virtual ~Neural_SB();

    void update(float timeElapsed);
};

#endif // NEURAL_SB_H
