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

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <cmath>
#include <boost/ptr_container/ptr_vector.hpp>

class NeuralLayer {
private :
    std::vector<float> m_X;
    std::vector< std::vector<float> > m_W;
    //Weights from prev layer to this layer.
    //The syntax is [prevLayer_NeuronNum][thisLayer_NeuronNum]
    std::vector<float> m_Delta;

    std::vector<float> m_Bias;   //ith Bias for the ith Neuron
    unsigned int m_iPrevNeurons;

    NeuralLayer * m_pPrev;
    NeuralLayer * m_pNext;

    float f(float x) //Activation function
    { return 1.0/(1 + exp(-x)); }

public :
    NeuralLayer(int num, int numPrevNeurons);
    ~NeuralLayer() {}

    NeuralLayer * prev() { return m_pPrev; }
    NeuralLayer * next() { return m_pNext; }

    void setPrev(NeuralLayer * nl) { m_pPrev = nl; }
    void setNext(NeuralLayer * nl) { m_pNext = nl; }

    void calculate();

    float& x(int num)            { return m_X[num]; }
    float& w(int from, int to)   { return m_W[from][to]; }
    float& d(int num)            { return m_Delta[num]; }
    float& b(int num)            { return m_Bias[num]; }
    int size()                  const { return m_X.size(); }

    void setDeltaZero() { std::fill(m_Delta.begin(), m_Delta.end(), 0.0f); }
};

class NeuralNetwork
{
private:
    boost::ptr_vector<NeuralLayer> m_Layers;
    std::vector<float> m_DesOutput;
    float m_fLearnRate;
    float m_fError;

    void calculateDelta(NeuralLayer *l);
    void calculateDelta();
    float ff(float x)
    { return x*(1.0 -x); }

    void setInput(const std::vector<float> & input);
    void calculate();
    void setDesiredOutput(const std::vector<float> & output);
    void backPropogate();

    void calculateError();
protected :
    int size(int layer) const { return m_Layers[layer].size(); }
    int numLayers() const { return m_Layers.size(); }
public:
    NeuralNetwork();
    virtual ~NeuralNetwork();

    void addLayer(int num);
    void randomWeights();

    float output(int num);
    int inputSize() const { return m_Layers.front().size(); }
    int outputSize() const { return m_Layers.back().size(); }

    void run(const std::vector<float> & input);
    void run(const std::vector<float> & input, std::vector<float> & out);
    float train(const std::vector<float> & input, const std::vector<float> & output);

    void setLearningRate(float r) { m_fLearnRate = r; }
    float getLearningRate() const  { return m_fLearnRate; }

    float & w(int l, int from, int to)
    { return m_Layers[l].w(from, to); }

    float & b(int l, int num)
    { return m_Layers[l].b(num); }

    void clear();
};

#endif // NEURALNETWORK_H
