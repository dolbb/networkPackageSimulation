#pragma once
#include <queue>
#include "Parameters.h"
#include "Event.h"
#include <vector>
#include "OutputPort.h"

using std::vector;
using std::priority_queue;

class Switcher
{
	int inputMaxTime;
	priority_queue<Event> events;
	vector<OutputPort> outputs;

public:
	//Ctor:
	Switcher(Parameters& p);

	//functions:
	bool packageStillRunning();
	void recieveAndDeliver(unsigned int time);
	void run();
	void printResults();
};

