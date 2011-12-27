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
