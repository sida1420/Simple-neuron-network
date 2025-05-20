#pragma once
#include <iostream>
#include "AI.h"
#include <vector>
#include <string>

using namespace std;

int main()
{
	AI* XORGateAI = new AI({5,3,3,1});

	while (true)
	{
		cout << "New loop started\n";
		cout << "Choose actions: [reset, run, train, visual, break]\n";
		string action="";


		cin>>action;

		if (action == "reset")
		{
			//reset
			delete XORGateAI;
			XORGateAI = new AI({ 5,3,3,1 });
		}
		else if (action == "run")
		{
			vector<float> inputs(5,0), outputs;
			cout << "Run chose, enter input:";
			for (int i = 0; i < 5; i++)
			{
				cin >> inputs[i];
			}

			outputs=XORGateAI->run(inputs);

			cout << "Output:";
			cout << outputs[0] << endl;
		}
		else if (action == "train")
		{
			//train
			//vector<pair<vector<float>, vector<float>>> data = { {{0,0} ,{0}},{{0,1},{1}}, {{1,0} ,{1}}, { { 1,1 } ,{0} } };
			/*vector<pair<vector<float>, vector<float>>> data = {
	{{0.0f, 0.0f, 0.0f}, {0.0f}},
	{{0.0f, 0.0f, 1.0f}, {1.0f}},
	{{0.0f, 1.0f, 0.0f}, {1.0f}},
	{{0.0f, 1.0f, 1.0f}, {0.0f}},
	{{1.0f, 0.0f, 0.0f}, {1.0f}},
	{{1.0f, 0.0f, 1.0f}, {0.0f}},
	{{1.0f, 1.0f, 0.0f}, {0.0f}},
	{{1.0f, 1.0f, 1.0f}, {1.0f}}
			};*/

			//vector<pair<vector<float>, vector<float>>> data = {
			//	// Inputs          Output (1 if odd number of 1s)
			//	{ { 0, 0, 0, 0 }, { 0 } }, 
			//	{ {0, 0, 0, 1}, {1} }, 
			//	{ {0, 0, 1, 0}, {1} }, 
			//	{ {0, 0, 1, 1}, {0} }, 
			//	{ {0, 1, 0, 0}, {1} }, 
			//	{ {0, 1, 0, 1}, {0} }, 
			//	{ {0, 1, 1, 0}, {0} }, 
			//	{ {0, 1, 1, 1}, {1} }, 
			//	{ {1, 0, 0, 0}, {1} }, 
			//	{ {1, 0, 0, 1}, {0} }, 
			//	{ {1, 0, 1, 0}, {0} },
			//	{ {1, 0, 1, 1}, {1} },
			//	{ {1, 1, 0, 0}, {0} }, 
			//	{ {1, 1, 0, 1}, {1} },
			//	{ {1, 1, 1, 0}, {1} }, 
			//	{ {1, 1, 1, 1}, {0} }  
			//};
			std::vector<std::pair<std::vector<float>, std::vector<float>>> data = {
				// Inputs {x4, x3, x2, x1, x0}, Output (1 if odd # of 1s)
				{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, {0.0f}}, // 0 ones
				{{0.0f, 0.0f, 0.0f, 0.0f, 1.0f}, {1.0f}}, // 1 one
				{{0.0f, 0.0f, 0.0f, 1.0f, 0.0f}, {1.0f}}, // 1 one
				{{0.0f, 0.0f, 0.0f, 1.0f, 1.0f}, {0.0f}}, // 2 ones
				{{0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, {1.0f}}, // 1 one
				{{0.0f, 0.0f, 1.0f, 0.0f, 1.0f}, {0.0f}}, // 2 ones
				{{0.0f, 0.0f, 1.0f, 1.0f, 0.0f}, {0.0f}}, // 2 ones
				{{0.0f, 0.0f, 1.0f, 1.0f, 1.0f}, {1.0f}}, // 3 ones
				{{0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, {1.0f}}, // 1 one
				{{0.0f, 1.0f, 0.0f, 0.0f, 1.0f}, {0.0f}}, // 2 ones
				{{0.0f, 1.0f, 0.0f, 1.0f, 0.0f}, {0.0f}}, // 2 ones
				{{0.0f, 1.0f, 0.0f, 1.0f, 1.0f}, {1.0f}}, // 3 ones
				//{{0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, {0.0f}}, // 2 ones
				{{0.0f, 1.0f, 1.0f, 0.0f, 1.0f}, {1.0f}}, // 3 ones
				{{0.0f, 1.0f, 1.0f, 1.0f, 0.0f}, {1.0f}}, // 3 ones
				{{0.0f, 1.0f, 1.0f, 1.0f, 1.0f}, {0.0f}}, // 4 ones
				{{1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, {1.0f}}, // 1 one
				{{1.0f, 0.0f, 0.0f, 0.0f, 1.0f}, {0.0f}}, // 2 ones
				{{1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, {0.0f}}, // 2 ones
				{{1.0f, 0.0f, 0.0f, 1.0f, 1.0f}, {1.0f}}, // 3 ones
				{{1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, {0.0f}}, // 2 ones
				{{1.0f, 0.0f, 1.0f, 0.0f, 1.0f}, {1.0f}}, // 3 ones
				{{1.0f, 0.0f, 1.0f, 1.0f, 0.0f}, {1.0f}}, // 3 ones
				{{1.0f, 0.0f, 1.0f, 1.0f, 1.0f}, {0.0f}}, // 4 ones
				{{1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, {0.0f}}, // 2 ones
				{{1.0f, 1.0f, 0.0f, 0.0f, 1.0f}, {1.0f}}, // 3 ones
				{{1.0f, 1.0f, 0.0f, 1.0f, 0.0f}, {1.0f}}, // 3 ones
				{{1.0f, 1.0f, 0.0f, 1.0f, 1.0f}, {0.0f}}, // 4 ones
				{{1.0f, 1.0f, 1.0f, 0.0f, 0.0f}, {1.0f}}, // 3 ones
				{{1.0f, 1.0f, 1.0f, 0.0f, 1.0f}, {0.0f}}, // 4 ones
				{{1.0f, 1.0f, 1.0f, 1.0f, 0.0f}, {0.0f}}, // 4 ones
				{{1.0f, 1.0f, 1.0f, 1.0f, 1.0f}, {1.0f}}  // 5 ones
			};

			cout << "Train chose, enter training limit, learning rate:";
			int limit;
			float learningRate;

			cin >> limit;
			cin >> learningRate;
			XORGateAI->train(data, limit, learningRate);
			
		}
		else if (action == "visual")
		{
			cout << "Visual chose\n";
			XORGateAI->visualAI();
		}
		else
		{
			break;
		}
	}
	delete XORGateAI;
	return 0;
}