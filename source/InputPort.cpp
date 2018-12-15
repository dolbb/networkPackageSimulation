#include <iostream>
#include <chrono>
#include <random>
#include "InputPort.h"
#include "Probability.h"

using std::cout;
using std::endl;

unsigned int InputPort::pickOutputIndex() {
	double random0to1Num = (double)rand() / (RAND_MAX);
	double currentSum = 0.0;
	int currentIndex = 0;
	for (std::vector<double>::iterator i = probs.begin() ; i != probs.end() ; ++i) {
		currentSum += *i;
		if (currentSum >= random0to1Num) {
			return currentIndex;
		}
		++currentIndex;
	}
	return 0;
}

void InputPort::set(double l, vector<double>& p) {
	lambda = l;
	probs = p;
}
Event InputPort::getNextEvent(double& prevEventTime)
{
	double nextMsgTime = getNextEventPoisson(lambda);	//time until next arrival.
	prevEventTime += nextMsgTime;						//the event's time.
	
	return Event(prevEventTime, Event::INCOMING_PACKAGE, pickOutputIndex());
}
