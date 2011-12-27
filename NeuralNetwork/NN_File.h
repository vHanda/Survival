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

#ifndef NN_FILE_H
#define NN_FILE_H

#include "NeuralNetwork.h"
#include <string>
#include <sstream>

class TiXmlElement;

class NN_File : public NeuralNetwork
{
private:
    //Loading Functions
    void loadNetwork(TiXmlElement * pNetwork);
    void loadWeights(TiXmlElement * pWeights);

    //Training Functions
    float trainSet(TiXmlElement * pSet);
    float train(TiXmlElement * pRoot);

    //Saving Functions
    void addStructure(TiXmlElement * pRoot);
    void addWeights(TiXmlElement * pRoot);
public:
    NN_File();
    virtual ~NN_File();

    void loadFromFile(const std::string & fileName);
    void saveToFile(const std::string & fileName);
    void train(const std::string & trainingSet);

};

template<typename T>
inline std::string toString(const T & t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // NN_FILE_H
