#pragma once

struct Event
{
	typedef enum Type{
		INCOMING_PACKAGE,
		FINISHED_PACKAGE
	}; 
	
	double timeStamp;
	int outputPort;
	Type type;

	Event(double time, Type t, int port):
		timeStamp(time),
		type(t),
		outputPort(port)
	{}
	
	bool operator<(const Event& e)const {
		return timeStamp < e.timeStamp;
	}
	
	bool operator>(const Event& e)const {
		return timeStamp > e.timeStamp;
	}
};

