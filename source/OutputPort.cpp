#include <iostream>
#include <chrono>
#include <random>
#include "OutputPort.h"
#include "Probability.h"

OutputPort::OutputPort(double m, unsigned int qSize)
{
	miu						= m;
	maxQueueSize			= qSize-1;
	workInProgress			= false;
	messagesInQueue			= 0;
	timeToEndCurrentSend	= 0;
	successfulMessages		= 0;
	failedMessages			= 0;

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
	return getNextEventExp(miu);
}

void OutputPort::putMsgInQueue()
{
	++messagesInQueue;
}

void OutputPort::dumpMsg()
{
	++failedMessages;
}

void OutputPort::setWorkingState(bool state)
{
	workInProgress = state;
}

void OutputPort::messageDelivered()
{
	++successfulMessages;
}

double OutputPort::takeFromQueue()
{
	--messagesInQueue;
	return timeToEndSending();
}

unsigned int OutputPort::getTotalSuccessfulMessages() {
	return successfulMessages;
}

unsigned int OutputPort::getTotalFailedMessages() {
	return failedMessages;
}

unsigned int OutputPort::getNumberOfWaitingMessages() {
	return messagesInQueue;
}
