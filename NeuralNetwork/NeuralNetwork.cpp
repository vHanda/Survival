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

#include "NeuralNetwork.h"
#include <iostream>

NeuralLayer::NeuralLayer(int num, int numPrevNeurons)
{
    m_X.resize(num, 0.0f);
    if(numPrevNeurons != 0)
        m_W.resize(numPrevNeurons, std::vector<float>(num));
    m_Bias.resize(num, 0.0f);
    m_Delta.resize(num, 0.0f);

    m_iPrevNeurons = numPrevNeurons;
    m_pPrev = NULL;
    m_pNext = NULL;
}

void NeuralLayer::calculate()
{
    if(m_pPrev == NULL)
        return;

    for(unsigned int i=0; i<m_X.size(); i++)
    {
        float sum = 0.0f;
        for(unsigned int j=0; j<m_iPrevNeurons; j++)
            sum += m_pPrev->x(j) * w(j, i);
        sum += m_Bias[i];
        m_X[i] = f(sum);
    }
}

void NeuralNetwork::addLayer(int num)
{
    if( m_Layers.empty() == true )
    {
        m_Layers.push_back( new NeuralLayer(num, 0) );
    }
    else
    {
        int prev = m_Layers.back().size();
        NeuralLayer * nl = new NeuralLayer(num, prev);
        nl->setPrev( &m_Layers.back() );
        m_Layers.back().setNext(nl);
        m_Layers.push_back( nl );
    }
}

void NeuralNetwork::setInput(const std::vector<float> & input)
{
    for(int i=0; i<m_Layers[0].size(); i++)
        m_Layers[0].x(i) = input[i];
}

void NeuralNetwork::calculate()
{
    for(unsigned int i=1; i<m_Layers.size(); i++)
        m_Layers[i].calculate();
}


void NeuralNetwork::calculateDelta(NeuralLayer * l)
{
    if(l->prev() == NULL)
        l->setDeltaZero();

    else if(l->next() == NULL)
    {
        //Output Layer
        for(int i=0; i<l->size(); i++)
        {
            l->d(i) = ff( l->x(i) ); //Derivative of the activation function
            l->d(i) *= (m_DesOutput[i] - l->x(i)); //Diff in output
        }
    }
    else
    {
        //Hidden Layer
        for(int i=0; i<l->size(); i++)
        {
            l->d(i) = 0.0f;
            NeuralLayer * n = l->next();
            for(int j=0; j< n->size(); j++)
                l->d(i) += n->w(i,j) * n->d(j); //This is the backpropogation

            l->d(i) *= ff( l->x(i) );
        }
    }
}


void NeuralNetwork::setDesiredOutput(const std::vector<float> & output)
{
    m_DesOutput = output;
}

void NeuralNetwork::backPropogate()
{
    calculateDelta();

    //Adjust te weights
    for(int l=m_Layers.size()-1; l>=1; l--) //Layer num
    {
        for(int i=0; i< m_Layers[l].size(); i++)
        {
            //Add dW to all the weights
            for(int k=0; k< m_Layers[l-1].size(); k++)
            {
                float dW = m_fLearnRate * m_Layers[l].prev()->x(k) * m_Layers[l].d(i);
                m_Layers[l].w(k, i) += dW;
            }

            float dW = m_fLearnRate * 1 * m_Layers[l].d(i);
            m_Layers[l].b(i) += dW;

        }
    }
}

float NeuralNetwork::output(int num)
{
    return m_Layers.back().x(num);
}

NeuralNetwork::NeuralNetwork()
{
    m_fLearnRate = 0.5;
}
NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::calculateDelta()
{
    for(unsigned int i=m_Layers.size()-1; i>=1; i--)
    {
        NeuralLayer * nl = &m_Layers[i];
        calculateDelta( nl );
    }
}

void NeuralNetwork::randomWeights()
{
    for(unsigned int l=1; l<m_Layers.size(); l++) //Layer num
        for(int i=0; i< m_Layers[l].size(); i++)
        {
            //Addjust W
            for(int k=0; k< m_Layers[l-1].size(); k++)
            {
                m_Layers[l].w(k, i) = (rand()%1000)/1000.0f;
                if( rand()%2 )
                    m_Layers[l].w(k, i) *= -1;
            }
        }

}

void NeuralNetwork::run(const std::vector<float> & input)
{
    setInput(input);
    calculate();
}

void NeuralNetwork::run(const std::vector<float> & input, std::vector<float> & out)
{
    run(input);
    for(int i=0; i<outputSize(); i++)
        out[i] = output(i);
}
float NeuralNetwork::train(const std::vector<float> & input,const std::vector<float> & output)
{
    run(input);
    setDesiredOutput(output);
    backPropogate();
    calculateError();
    return m_fError;
}

void NeuralNetwork::clear()
{
    m_Layers.clear();
    m_DesOutput.clear();
}

void NeuralNetwork::calculateError()
{
    float error = 0.0f;
    for(unsigned int i=0; i<m_DesOutput.size(); i++)
        error += (m_DesOutput[i] - output(i)) * (m_DesOutput[i] - output(i));
    m_fError = error / outputSize();
    //std::cout << outputSize() << "-----" << error << std::endl;
}
