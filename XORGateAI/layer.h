#pragma once
#include "neuron.h"
#include <iostream>
class layer
{
public:
	bool inputLayer;

	int numberOfNeurons;

	std::vector<neuron*> neurons;

	layer(int,int,bool);
	~layer();
};

