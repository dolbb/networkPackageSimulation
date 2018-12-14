#include <iostream>
#include "Parameters.h"
#include "Switcher.h"

int main(int argc, char **argv) {
	Parameters p(argc, argv);	//get the params from activation command line.
	
	Switcher switcher(p);		//get events from inputs.
	switcher.run();
	switcher.printResults();

	return 0;
	//TODO: delete:
	//while (workingTime < p.t || switcher.packageStillRunning()) {
	//	switcher.recieveAndDeliver(workingTime++);
	//	cout << "======   " << workingTime << "   ======" << endl;
	//}
}