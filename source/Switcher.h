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
	double inputMaxTime;
	double currentRunTime;
	priority_queue<Event,vector<Event>,greater<Event>> events;
	vector<OutputPort> outputs;

	//inner functions:
	void handleInputEvent(Event& currentEvent);
	void handleOutputEvent(Event& currentEvent);

public:
	//Ctor will create all input events in the Switcher:
	Switcher(Parameters& p);

	//functions:
	bool packageStillRunning();
	void run();
	void recieveAndDeliver(unsigned int time);
	void printResults();
};

