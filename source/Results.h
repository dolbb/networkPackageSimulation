#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct Results
{
	int totalSuccessfulMsgNum;
	vector<int> successfulMsgNum;
	int totalMsgDumpedNum;
	vector<int> MsgDumpedNum;
	int totalTime;
	long double avgWaitTime;
	long double avgHandleTime;

	Results(int t) {
		totalSuccessfulMsgNum	= 0;
		totalMsgDumpedNum		= 0;
		totalTime				= t;
		avgWaitTime				= 0.0;
		avgHandleTime			= 0.0;
	}

	void print() {
		cout << totalSuccessfulMsgNum << ' ';
		for (unsigned int i = 0; i < successfulMsgNum.size(); ++i) {
			cout << successfulMsgNum[i] << ' ';
		}
		cout << totalMsgDumpedNum << ' ';
		for (unsigned int i = 0; i < MsgDumpedNum.size(); ++i) {
			cout << MsgDumpedNum[i] << ' ';
		}
		cout << totalTime << ' ';
		cout << avgWaitTime << ' ';
		cout << avgHandleTime << ' ' << endl;
	}
};

