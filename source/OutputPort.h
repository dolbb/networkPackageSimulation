#pragma once
#include <vector>

using namespace std;

class OutputPort
{
	//init constant data:
	double miu;
	unsigned int maxQueueSize;
	bool workInProgress;
	
	//dynamic data:
	unsigned int messagesInQueue;
	unsigned int timeToEndCurrentSend;
	unsigned int successfulMessages;
	unsigned int failedMessages;

	unsigned long totalWaitingTicks;
	unsigned long totalHandlingTicks;

public:
	OutputPort(double m, unsigned int qSize);
	bool isWorking();
	bool isQueueFull();
	bool isQueueEmpty();
	double timeToEndSending();
	void putMsgInQueue();
	void dumpMsg();
	void setWorkingState(bool state);
	double takeFromQueue(); //returns time to finish the next msg.
	unsigned int getTotalSuccessfulMessages();
	unsigned int getTotalFailedMessages();
	
	//TODO: replace following functions:
	unsigned long getTotalWaitingTicks();
	unsigned long getTotalHandlingTicks();
};

