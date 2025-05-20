#include "AI.h"


float derivativeZPerW(float a)
{
	return a;
}

constexpr float e2 = 2.718281f;
float sigmoid2(float x)
{
	return 1.f / (1.f + pow(e2, -x));
}

float derivativeAPerZ(float z)
{
	return sigmoid2(z) * (1 - sigmoid2(z));
}

float derivativeCPerA(float a, float y)
{
	return 2.f * (a - y);
}





AI::AI(vector<int> layersSize)
{
	std::cout << "Construct AI\n";
	//layers.reserve(layersSize.size());
	numberOflayers = layersSize.size();


	layers.push_back(new layer(layersSize[0], 0,true));

	for (int i = 1; i < numberOflayers; i++)
	{
		layers.push_back(new layer(layersSize[i], layersSize[i - 1],true));
	}


}

AI::~AI()
{
	for (int l = 0; l < numberOflayers; l++)
	{
		delete layers[l];
	}
	layers.clear();
}

void AI::train(vector<pair<vector<float>, vector<float>>> data,int limit, float learningRate)
{
	int count = 0;
	while (count < limit)
	{
		count++;
		cout << count << "st generation\n";

		vector<layer*> gradientDescent;
		for (int l = 0; l < numberOflayers - 1; l++)
		{
			gradientDescent.push_back(new layer(layers[l + 1]->numberOfNeurons, layers[l]->numberOfNeurons,false));
		}
		

		for (int d = 0; d < data.size(); d++)
		{
			float cost=0;
			vector<float> input = data[d].first;
			vector<float> desiredOutput = data[d].second;

			vector<float> output=run(input);
			//calculating cost
			for (int o = 0; o < output.size(); o++)
			{
				cost += pow(output[o] - desiredOutput[0], 2.f);
			}
			cout << cost << "\n";
			//cout << "Reset gradient descent\n";
			for (int l = 0; l < numberOflayers - 1; l++)
			{
				for (int n = 0; n < gradientDescent[l]->numberOfNeurons; n++)
				{
					gradientDescent[l]->neurons[n]->value = 0;
				}
			}

			for (int n = 0; n < gradientDescent[numberOflayers - 2]->numberOfNeurons; n++)
			{
				gradientDescent[numberOflayers - 2]->neurons[n]->value = 
					derivativeCPerA(layers[numberOflayers - 1]->neurons[n]->value, desiredOutput[n])
					*derivativeAPerZ(layers[numberOflayers - 1]->neurons[n]->rawValue);
				for (int w = 0; w < gradientDescent[numberOflayers - 2]->neurons[n]->weights.size(); w++)
				{
					gradientDescent[numberOflayers - 2]->neurons[n]->weights[w] += gradientDescent[numberOflayers - 2]->neurons[n]->value * layers[numberOflayers-2]->neurons[w]->value;
					gradientDescent[numberOflayers - 3]->neurons[w]->value += gradientDescent[numberOflayers - 2]->neurons[n]->value * layers[numberOflayers - 1]->neurons[n]->weights[w];
				}

				gradientDescent[numberOflayers - 2]->neurons[n]->bias += gradientDescent[numberOflayers - 2]->neurons[n]->value;
			}
			for (int l = numberOflayers - 3; l >= 0; l--)
			{
				for (int n = 0; n < gradientDescent[l]->numberOfNeurons; n++)
				{
					gradientDescent[l]->neurons[n]->value *= derivativeAPerZ(layers[l + 1]->neurons[n]->rawValue);

					for (int w = 0; w < gradientDescent[l]->neurons[n]->weights.size(); w++)
					{
						gradientDescent[l]->neurons[n]->weights[w] += gradientDescent[l]->neurons[n]->value * layers[l]->neurons[w]->value;
						if (l > 0) gradientDescent[l - 1]->neurons[w]->value += gradientDescent[l]->neurons[n]->value * layers[l + 1]->neurons[n]->weights[w];
					}
					gradientDescent[l]->neurons[n]->bias+= gradientDescent[l]->neurons[n]->value;
				}
			}

			
		}

		for (int l = 0; l < numberOflayers - 1; l++)
		{
			for (int n = 0; n < gradientDescent[l]->numberOfNeurons; n++)
			{
				for (int w = 0; w < gradientDescent[l]->neurons[n]->weights.size(); w++)
				{
					gradientDescent[l]->neurons[n]->weights[w] /= (float)data.size();
					layers[l + 1]->neurons[n]->weights[w] -= learningRate *(gradientDescent[l]->neurons[n]->weights[w]-2.f* layers[l + 1]->neurons[n]->weights[w]*0.0001f);

				}
				gradientDescent[l]->neurons[n]->bias /= (float)data.size();
				layers[l + 1]->neurons[n]->bias -= learningRate*gradientDescent[l]->neurons[n]->bias;
			}
		}
		

		for (layer* l_ptr : gradientDescent) {
			delete l_ptr;
		}
		gradientDescent.clear();
	}
	std::cout << "\nTraining finished\n";
}

vector<float> AI::run(vector<float> inputs)
{
	for (int i = 0; i < inputs.size(); i++)
	{
		layers[0]->neurons[i]->value = inputs[i];
	}
	for (int i = 1; i < layers.size(); i++)
	{
		for (int j = 0; j < layers[i]->neurons.size(); j++)
		{
			float value = layers[i]->neurons[j]->bias;

			for (int k = 0; k < layers[i - 1]->neurons.size(); k++)
			{
				value += layers[i - 1]->neurons[k]->value * layers[i]->neurons[j]->weights[k];
			}


			layers[i]->neurons[j]->rawValue= value;
			layers[i]->neurons[j]->value= sigmoid2(value);

		}
	}

	int outputsSize = layers[layers.size() - 1]->neurons.size();
	vector<float> outputs;

	for (int n = 0; n < outputsSize; n++)
	{
		outputs.push_back(layers[layers.size() - 1]->neurons[n]->value);
	}

	return outputs;
}

void AI::visualAI()
{
	for (int l = 0; l < numberOflayers; l++)
	{
		for (int n = 0; n < layers[l]->numberOfNeurons; n++)
		{
			std::cout << layers[l]->neurons[n]->value<<"/"<< layers[l]->neurons[n]->bias << "";
			if (!layers[l]->inputLayer)
			{
				cout << "[";
				for (int w = 0; w < layers[l]->neurons[n]->weights.size(); w++)
				{
					cout << layers[l]->neurons[n]->weights[w];
					if (w < layers[l]->neurons[n]->weights.size() - 1) cout << ",";
				}cout << "]";
			}
			cout << " ";
		}
		cout << endl;
	}
}
