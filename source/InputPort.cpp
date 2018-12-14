#include <iostream>
#include <chrono>
#include <random>
#include "InputPort.h"
#include "Probability.h"

unsigned int InputPort::pickOutputIndex() {
	srand(time(NULL));
	double random0to1Num = (double)rand() / (RAND_MAX);
	double currentSum = 0.0;
	int currentIndex = 0;
	for (std::vector<double>::iterator i = probs.begin(); (i != probs.end()); ++i) {
		currentSum += *i;
		if (currentSum >= random0to1Num) {
			return currentIndex;
		}
	}
	return 0;
}

InputPort::InputPort(double l, vector<double>& p)
{
	lambda = l;
	probs = p;
	timeToPackage = getTicksPoisson(lambda);
}

int InputPort::getMessage()
{
	int outIndex = -1;
	if(--timeToPackage <= 0){
		//calculate new time to next package:
		timeToPackage = getTicksPoisson(lambda);
		cout << "random got: " << timeToPackage << endl; //TODO: delete after debug
		//pick output:
		outIndex = pickOutputIndex();
	}
	return outIndex;
}
