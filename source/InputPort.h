#pragma once
#include <vector>

using namespace std;

class InputPort
{
	double lambda;
	vector<double> probs;
	int timeToPackage;

	unsigned int pickOutputIndex();

public:
	InputPort(double l, vector<double>& p);
	int getMessage();
};

