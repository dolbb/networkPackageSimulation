#include <chrono>
#include <random>
#include "Probability.h"

double getNextEventPoisson(double lambda){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::poisson_distribution<int> distribution(lambda);
	return 1.0 / distribution(generator);
}

double getNextEventExp(double miu){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::exponential_distribution<double> distribution(miu);
	return distribution(generator);
}

