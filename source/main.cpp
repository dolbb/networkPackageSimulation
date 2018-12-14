#include <iostream>
#include "Parameters.h"
#include "Switcher.h"

int main(int argc, char **argv) {
	unsigned int workingTime = 0;
	Parameters p(argc, argv);	//get the params from activation command line.
	Switcher switcher(p);
	
	while (workingTime < p.t || switcher.packageStillRunning()) {
		switcher.recieveAndDeliver(workingTime++);
		cout << "======   " << workingTime << "   ======" << endl;
	}

	switcher.printResults(workingTime);

	return 0;
}