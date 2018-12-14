#include <iostream>
#include <chrono>
#include <random>
#include "OutputPort.h"
#include "Probability.h"

OutputPort::OutputPort(double m, unsigned int qSize)
{
	miu						= m;
	maxQueueSize			= qSize;
	workInProgress			= false;
	messagesInQueue			= 0;
	timeToEndCurrentSend	= 0;
	successfulMessages		= 0;
	failedMessages			= 0;
	totalWaitingTicks		= 0;
	totalHandlingTicks		= 0;
}

bool OutputPort::isWorking()
{
	return workInProgress;
}

void OutputPort::handleMsg()
{
	if (workInProgress) {
		if (--timeToEndCurrentSend == 0) {
			workInProgress = false;
			++successfulMessages;
		}
	}
	
	//check queue for waiting msgs, and start sending them:
	if ((!workInProgress) && (messagesInQueue > 0)) {
		workInProgress = true;
		timeToEndCurrentSend = getTicksPoisson(miu);
	}

	//add currently stored/handled msgs:
	totalWaitingTicks	+= messagesInQueue;
	totalHandlingTicks	+= workInProgress ? 1 : 0 ;
}

void OutputPort::putMsgInQueue()
{
	//if possible - start sending msg:
	if (!isWorking()) {
		workInProgress = true;
		timeToEndCurrentSend = getTicksPoisson(miu);
	}
	//if cpu busy, try to put in queue:
	else if(messagesInQueue < maxQueueSize){
		++messagesInQueue;
	}
	//if queue full, dump msg:
	else {
		++failedMessages;
	}
}

unsigned long OutputPort::getTotalWaitingTicks() {
	return totalWaitingTicks;
}

unsigned long OutputPort::getTotalHandlingTicks() {
	return totalHandlingTicks;
}

unsigned int OutputPort::getTotalSuccessfulMessages() {
	return successfulMessages;
}

unsigned int OutputPort::getTotalFailedMessages() {
	return failedMessages;
}