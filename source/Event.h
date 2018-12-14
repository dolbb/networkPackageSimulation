#pragma once

struct Event
{
	typedef enum EventType {
		INCOMING_PACKAGE,
		FINISHED_PACKAGE
	}; 
	
	double timeStamp;
	int outputPort;
	EventType type;

	Event(double time, EventType t, int port):
		timeStamp(time),
		type(t),
		outputPort(port)
	{}
	
	bool operator<(Event& e) {
		return timeStamp < e.timeStamp;
	}
};

