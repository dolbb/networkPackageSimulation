#include "Switcher.h"
#include "Results.h"



Switcher::Switcher(Parameters& p)
{
	t = p.t;

	//init inputs:
	for (unsigned int i = 0; i < p.n; ++i) {
		inputs.push_back(InputPort(p.lambdas[i], p.probs[i]));
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

void Switcher::recieveAndDeliver(unsigned int workingTime)
{
	//output ports should now iterate one clock cycle on the msg deliveries.
	for (std::vector<OutputPort>::iterator i = outputs.begin(); (i != outputs.end()); ++i) {
		i->handleMsg();
	}

	//get messages from input ports to the wanted output port:
	for (std::vector<InputPort>::iterator i = inputs.begin() ; (i != inputs.end()) && (workingTime < t); ++i) {
		//get output index or -1 if a msg wasnt recieved:
		int msgDestination = i->getMessage();
		if (msgDestination >= 0) {
			//if a msg was recieved tell the right output port to put in queue or start working on it:
			outputs[msgDestination].putMsgInQueue();
		}
	}
}

void Switcher::printResults(unsigned int totalTime) {
	Results res(totalTime);
	long totalWaitTicks = 0;
	long totalHandleTicks = 0;

	for (unsigned int i = 0; i < outputs.size(); ++i) {
		//save successful results:
		res.totalSuccessfulMsgNum += outputs[i].getTotalSuccessfulMessages();
		res.successfulMsgNum.push_back(outputs[i].getTotalSuccessfulMessages());
		
		//save dumped results:
		res.totalMsgDumpedNum += outputs[i].getTotalFailedMessages();
		res.MsgDumpedNum.push_back(outputs[i].getTotalFailedMessages());

		totalWaitTicks += outputs[i].getTotalWaitingTicks();
		totalHandleTicks += outputs[i].getTotalHandlingTicks();
	}
	
	res.avgWaitTime = totalWaitTicks / totalTime;
	res.avgHandleTime = totalHandleTicks / totalTime;

	res.print();
}