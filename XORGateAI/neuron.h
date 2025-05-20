#pragma once
#include <vector>
#include <random>


class neuron
{
public:
	float value;
	float rawValue;
	float bias;
	
	std::vector<float> weights;

	neuron(int,bool);


};

