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

bool OutputPort::isQueueFull()
{
	return maxQueueSize == messagesInQueue;
}

bool OutputPort::isQueueEmpty()
{
	return messagesInQueue == 0;
}

double OutputPort::timeToEndSending()
{
	return getNextEventPoisson(miu);
}

void OutputPort::putMsgInQueue()
{
	++messagesInQueue;
}

void OutputPort::dumpMsg()
{
	failedMessages++;
}

void OutputPort::setWorkingState(bool state)
{
	workInProgress = state;
}

double OutputPort::takeFromQueue()
{
	--messagesInQueue;
	return getNextEventPoisson(miu);
}

unsigned int OutputPort::getTotalSuccessfulMessages() {
	return successfulMessages;
}

unsigned int OutputPort::getTotalFailedMessages() {
	return failedMessages;
}

//====================================================
//			TODO: replace following functions:
//====================================================
unsigned long OutputPort::getTotalWaitingTicks() {
	return totalWaitingTicks;
}

unsigned long OutputPort::getTotalHandlingTicks() {
	return totalHandlingTicks;
}
