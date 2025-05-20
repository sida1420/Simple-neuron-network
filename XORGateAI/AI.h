#pragma once
#include <vector>
#include <cmath>
#include "layer.h"
#include <iostream>
using namespace std;


class AI
{

private:
	vector<layer*> layers;
	int numberOflayers;

public:
	AI(vector<int>);
	~AI();

	void train(vector<pair<vector<float>, vector<float>>>, int, float);

	vector<float> run(vector<float>);

	void visualAI();
};

