#pragma once
#include <vector>
#include "Event.h"

using std::vector;

class InputPort
{
	double lambda;
	vector<double> probs;

	unsigned int pickOutputIndex();

public:
	void set(double l, vector<double>& p);
	Event getNextEvent(double& prevEventTime);
};

