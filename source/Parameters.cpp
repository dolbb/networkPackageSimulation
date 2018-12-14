#include "Parameters.h"
#include <iostream>
#include <sstream>

static void getParam(char** argv, unsigned int& result, int index) {
	istringstream inputT(argv[index]);
	inputT >> result;
}

static void getParam(char** argv, double& result, int index) {
	istringstream inputT(argv[index]);
	inputT >> result;
}

Parameters::Parameters(int argc, char **argv)
{
	if (argc <= 1) {
		t = 1;
		n = 1;
		m = 1;
		vector<double> v;
		v.push_back(0.5);
		probs.push_back(v);
		lambdas.push_back(2);
		queueSizes.push_back(1);
		mius.push_back(1/3);
	}
	else {
		int indexCounter = 1;
		getParam(argv, t, indexCounter++);
		getParam(argv, n, indexCounter++);
		getParam(argv, m, indexCounter++);
		for (unsigned int i = 0; i < n; ++i) {
			vector<double> line;
			line.resize(m);
			for (unsigned int j = 0; j < m; ++j) {
				getParam(argv, line[j], indexCounter++);
			}
			probs.push_back(line);
			line.clear();
		}

		lambdas.resize(n);
		for (unsigned int i = 0; i < n; ++i) {
			getParam(argv, lambdas[i], indexCounter++);
		}
		
		queueSizes.resize(m);
		for (unsigned int i = 0; i < m; ++i) {
			getParam(argv, queueSizes[i], indexCounter++);
		}

		mius.resize(m);
		for (unsigned int i = 0; i < m; ++i) {
			getParam(argv, mius[i], indexCounter++);
		}
	}
}


/*===================================================
**				for testing purposes:	
===================================================*/
void Parameters::printProbability() {
	cout << "switching probability matrix:" << endl;
	for (std::vector<vector<double>>::iterator i = probs.begin(); i != probs.end(); ++i) {
		for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Parameters::print()
{
	int x;
	cout << "============== printing the input ==============" << endl;
	cout << "time:                  " << t << endl;
	cout << "number of inputs:      " << n << endl;
	cout << "number of outputs:     " << m << endl << endl;
	
	//print lambdas:
	printProbability();
	
	//print lambdas:
	cout << "lambda values:" << endl;
	for (std::vector<double>::iterator i = lambdas.begin(); i != lambdas.end(); ++i) {
		cout << *i << ' ';
	}
	//print queue sizes:
	cout << endl << "queue sizes:" << endl;
	for (std::vector<unsigned int>::iterator i = queueSizes.begin(); i != queueSizes.end(); ++i) {
		cout << *i << ' ';
	}
	//print mius:
	cout << endl << "mues values:" << endl;
	for (std::vector<double>::iterator i = mius.begin(); i != mius.end(); ++i) {
		cout << *i << ' ';
	}
	cout << endl << "===================== END ======================" << endl;
	cin >> x;
}
