#include "Switcher.h"
#include "Results.h"
#include "InputPort.h"


/*=====================================================================
*						private functions
=====================================================================*/
void Switcher::handleInputEvent(Event& e) {
	int outputIndex = e.outputPort;
	//try the first of the following 3 options:
	//1 - try to start sending the message using the right output port:
	if (outputs[outputIndex].isWorking() == false) {
		double finishSendingTime = outputs[outputIndex].timeToEndSending();
		totalServiceTime += finishSendingTime;
		finishSendingTime += e.timeStamp;
		events.push(Event(finishSendingTime, Event::FINISHED_PACKAGE, outputIndex));
		outputs[outputIndex].setWorkingState(true);
	}
	//2 - try to put in queue for the right output port:
	else if (outputs[outputIndex].isQueueFull() == false) {
		outputs[outputIndex].putMsgInQueue();
	}
	//3 - dump package:
	else {
		outputs[outputIndex].dumpMsg();
	}
}

void Switcher::handleOutputEvent(Event& e) {
	int outputIndex = e.outputPort;
	//if the queue is empty - creat a new finished even otherwise:
	if (outputs[outputIndex].isQueueEmpty()) {
		//if nothing waits for the server - set it to idle:
		outputs[outputIndex].setWorkingState(false);
	}
	else {
		//get package's service time:
		double finishSendingTime = outputs[outputIndex].takeFromQueue();
		//add it to total service time for statistics:
		totalServiceTime += finishSendingTime;
		//add current event time in order to update the relative time to a simulation's absolute:
		finishSendingTime += e.timeStamp;
		//add the new event to queue:
		events.push(Event(finishSendingTime, Event::FINISHED_PACKAGE, outputIndex));
	}
}

void Switcher::updateStatistics(Event& currentEvent){

	//get the last active delta - thats the amount of time each waiting package has waited:
	double deltaBetweenEvents = currentEvent.timeStamp - currentRunTime;

	for (std::vector<OutputPort>::iterator i = outputs.begin(); (i != outputs.end()); ++i) {
		totalWaitingTime += deltaBetweenEvents * i->getNumberOfWaitingMessages();
	}
	//set the simulation's runtime to the event's timestamp:
	currentRunTime = currentEvent.timeStamp;
}

/*=====================================================================
*						public functions
=====================================================================*/
Switcher::Switcher(Parameters& p)
{
	inputMaxTime = p.t;
	currentRunTime = 0.0;
	double prevEventTime;
	InputPort inputPort;

	//put input events into the event simulation:
	for (unsigned int i = 0; i < p.n; ++i) {
		prevEventTime = 0.0;	
		inputPort.set(p.lambdas[i], p.probs[i]);
		while (true) {
			Event tempEvent = inputPort.getNextEvent(prevEventTime);
			if (tempEvent.timeStamp <= inputMaxTime) {
				events.push(tempEvent);
			}
			else {
				break;
			}
		}
	}
	
	//init outputs:
	for (unsigned int i = 0; i < p.m; ++i) {
		outputs.push_back(OutputPort(p.mius[i], p.queueSizes[i]));
	}
}

bool Switcher::packageStillRunning()
{
	for (std::vector<OutputPort>::iterator i = outputs.begin(); i != outputs.end(); ++i) {
		if (i->isWorking()) {
			return true;
		}
	}
	return false;
}

void Switcher::run() {
	while (events.empty() == false) {
		//take current event from the event queue:
		Event currentEvent = events.top();

		//use the matching handle function for an event:
		if (currentEvent.type == Event::INCOMING_PACKAGE) {
			handleInputEvent(currentEvent);
		}
		else {
			handleOutputEvent(currentEvent);
		}

		//for statistics purposes we will save the data in order to calculate average wait / handle times:
		updateStatistics(currentEvent);

		//remove the current event:
		events.pop();
	}
}

void Switcher::printResults() {	
	Results res(currentRunTime);

	for (unsigned int i = 0; i < outputs.size(); ++i) {
		//save successful results:
		res.totalSuccessfulMsgNum += outputs[i].getTotalSuccessfulMessages();
		res.successfulMsgNum.push_back(outputs[i].getTotalSuccessfulMessages());
		
		//save dumped results:
		res.totalMsgDumpedNum += outputs[i].getTotalFailedMessages();
		res.MsgDumpedNum.push_back(outputs[i].getTotalFailedMessages());
	}
	
	res.avgWaitTime = totalWaitingTime / res.totalSuccessfulMsgNum;
	res.avgServiceTime = totalServiceTime / res.totalSuccessfulMsgNum;

	res.print();
}