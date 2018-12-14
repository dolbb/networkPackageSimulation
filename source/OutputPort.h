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
	void handleMsg();
	void putMsgInQueue();
	unsigned long getTotalWaitingTicks();
	unsigned long getTotalHandlingTicks();
	unsigned int getTotalSuccessfulMessages();
	unsigned int getTotalFailedMessages();
};

