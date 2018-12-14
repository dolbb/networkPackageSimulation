#pragma once
#include "Parameters.h"
#include "InputPort.h"
#include "OutputPort.h"

class Switcher
{
	unsigned int t;
	vector<InputPort> inputs;
	vector<OutputPort> outputs;

public:
	//Ctor:
	Switcher(Parameters& p);

	//functions:
	bool packageStillRunning();
	void recieveAndDeliver(unsigned int time);
	void printResults(unsigned int totalTime);
};

