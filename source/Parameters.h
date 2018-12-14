#pragma once
#include <vector>

using namespace std;


class Parameters
{
public:
	double t;						//sender simulation time.
	unsigned int n;					//recieving ports' number.
	unsigned int m;					//exiting ports' number.
	vector<vector<double>> probs;	//probability matrix.
	vector<double> lambdas;			//input lambdas' vector.
	vector<unsigned int> queueSizes;//output queue sizes.
	vector<double> mius;			//output mius' vector.
	
	/*	CTor:	*/
	Parameters(int argc, char **argv);

	/*	for testing purposes:	*/
	void printProbability();
	void print();
};

