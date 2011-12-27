#include "../tinyxml/tinyxml.h"
#include "NN_File.h"

NN_File::NN_File()
{
}

NN_File::~NN_File()
{
}

//
// Training the Neural Network
//
void NN_File::train(const std::string & trainingSet)
{
    TiXmlDocument doc(trainingSet);
    doc.LoadFile();

    TiXmlElement * pRoot = doc.RootElement();
    loadNetwork(pRoot->FirstChildElement("neuralnetwork"));

    randomWeights();

    double minError;
    pRoot->Attribute("error", &minError);
    minError /= 100.0;

    // Training
    float error = 100.0;
    while( error > minError )
    {
        error = train(pRoot);
        std::cout << "Error : " << error *100 << std::endl;
    }
}

float NN_File::train(TiXmlElement * pRoot)
{
    TiXmlElement * pSet = pRoot->FirstChildElement("set");

    float error = 0.0f;
    int i;
    for(i=0; pSet != NULL; i++)
    {
        float e = trainSet(pSet);
        error += e;
        //std::cout << "\t\t E : " << e << std::endl;
        pSet = pSet->NextSiblingElement("set");
    }
    return error/i;
}

float NN_File::trainSet(TiXmlElement * pSet)
{
    std::vector<float> input(inputSize());
    std::vector<float> out(outputSize());

    //Get input and output from Set
    TiXmlElement * pInput = pSet->FirstChildElement("i");
    for(int i=0; i<inputSize(); i++)
    {
        input[i] = atof(pInput->GetText());
        pInput = pInput->NextSiblingElement("i");
    }

    TiXmlElement * pOutput = pSet->FirstChildElement("o");
    for(int i=0; i<outputSize(); i++)
    {
        out[i] = atof(pOutput->GetText());
        pOutput = pOutput->NextSiblingElement("o");
    }

    //Train the network. Returns the error.
    return NeuralNetwork::train(input, out);
}

//
//Saving the Neural network to an xml file
//
void NN_File::saveToFile(const std::string & fileName)
{
    TiXmlDocument doc;
    TiXmlElement * pRoot = new TiXmlElement("neuralnetwork");
    doc.LinkEndChild(pRoot);

    addStructure(pRoot);
    addWeights(pRoot);

    doc.SaveFile(fileName);
}

void NN_File::addStructure(TiXmlElement * pRoot)
{
    for(int i=0; i<numLayers(); i++)
    {
        TiXmlElement * pLayer = new TiXmlElement("layer");
        pLayer->SetAttribute("neuron", size(i));

        pRoot->LinkEndChild(pLayer);
    }
}
void NN_File::addWeights(TiXmlElement * pRoot)
{
    TiXmlElement * pWeights = new TiXmlElement("weights");
    for(int l=1; l<numLayers(); l++)
    {
        TiXmlElement * pLayer = new TiXmlElement("layer");
        pLayer->SetAttribute("num", l);

        int neurons = size(l);
        int prevLayerNeurons = size(l-1);

        //Neuron Weights
        for(int i=0; i<neurons; i++) //current layer neuron
        {
            TiXmlElement * pNeuron = new TiXmlElement("neuron");
            for(int j=0; j<prevLayerNeurons; j++) //j is each neuron of the prev layer
            {
                TiXmlElement * pW = new TiXmlElement("w");

                float weight = w(l, j, i);
                TiXmlText * pText = new TiXmlText( toString(weight) );
                pW->LinkEndChild(pText);

                pNeuron->LinkEndChild(pW);
            }
            //Bias
            TiXmlElement * pBias = new TiXmlElement("bias");
            float bias = b(l, i);
            TiXmlText * pText = new TiXmlText( toString(bias) );
            pBias->LinkEndChild(pText);
            pNeuron->LinkEndChild(pBias);

            //Link Neuron to the layers
            pLayer->LinkEndChild(pNeuron);
        }

        pWeights->LinkEndChild(pLayer);
    }
    pRoot->LinkEndChild(pWeights);
}

//
// Creating Neural Network from file
//
void NN_File::loadFromFile(const std::string & fileName)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();

    TiXmlElement * pRoot = doc.RootElement();

    loadNetwork(pRoot);
    loadWeights(pRoot->FirstChildElement("weights"));
}

void NN_File::loadNetwork(TiXmlElement * pNetwork)
{
    clear();

    TiXmlElement * pLayer = pNetwork->FirstChildElement("layer");
    while(pLayer != NULL)
    {
        int num;
        pLayer->Attribute("neuron", &num);
        addLayer(num);

        pLayer = pLayer->NextSiblingElement("layer");
    }
    /*
    std::cout << "----- Neural Network ------\n";
    std::cout << "Num of Layers : " << numLayers() << "\n";
    for(int i=0; i<numLayers(); i++)
        std::cout << "Layer #" << i << " : " << size(i) << "\n";
    std::cout << "----------------------------" << std::endl;
    */
}

void NN_File::loadWeights(TiXmlElement * pWeights)
{
    //std::cout << "Loading Wieghts : " << std::endl;

    TiXmlElement * pLayer = pWeights->FirstChildElement("layer");
    while(pLayer != NULL)
    {
        int layerNum;
        pLayer->Attribute("num", &layerNum);

        TiXmlElement * pNeuron = pLayer->FirstChildElement("neuron");
        for(int n=0; pNeuron != NULL && n <size(layerNum); n++)
        //n accesses this layer's neurons
        {
            TiXmlElement * pW = pNeuron->FirstChildElement("w");
            for(int i=0; pW != NULL && i<size(layerNum-1); i++)
            //i stands for the prev layer's neurons.
            {
                float value = atof(pW->GetText());
                w(layerNum, i, n) = value;

                pW = pW->NextSiblingElement("w");
            }

            //Bias
            TiXmlElement * pBias = pNeuron->FirstChildElement("bias");
            float bias = atof(pBias->GetText());
            b(layerNum, n) = bias;

            pNeuron = pNeuron->NextSiblingElement("neuron");
        }
        pLayer = pLayer->NextSiblingElement("layer");
    }
}
