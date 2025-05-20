
#include "layer.h"

layer::layer(int numberOfNeurons, int numberOfNeuronsPreLayer, bool randomize)
{
	//std::cout << "Construct layer\n";
	if (numberOfNeuronsPreLayer == 0) inputLayer = true;
	else inputLayer = false;

	this->numberOfNeurons = numberOfNeurons;



	for (int i = 0; i < numberOfNeurons; i++) {
		neurons.push_back(new neuron(numberOfNeuronsPreLayer,randomize));
	}

}

layer::~layer()
{
	for (int n = 0; n < numberOfNeurons; n++)
	{
		delete neurons[n];
	}
	neurons.clear();
}
