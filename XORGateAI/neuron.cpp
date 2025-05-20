#include "neuron.h"
#include <iostream>
neuron::neuron(int numberOfNeuronsPreLayer,bool randomize)
{
	//std::cout << "Construct neuron\n";
	weights.resize(numberOfNeuronsPreLayer);
    if (randomize)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distrib_weights(-0.5f,0.5f);

        for (int i = 0; i < numberOfNeuronsPreLayer; i++)
        {
            weights[i] = distrib_weights(gen);
        }
        bias = 0.0f;
    }
    else
    {
        for (int i = 0; i < numberOfNeuronsPreLayer; i++)
        {
            weights[i] = 0.0f;
        }
        bias = 0.0f;
    }

	value = 0.f;
	rawValue = 0.f;
}



