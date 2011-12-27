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
