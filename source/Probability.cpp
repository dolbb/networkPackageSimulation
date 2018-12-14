#include <chrono>
#include <random>
#include "Probability.h"

int getTicksPoisson(double lambda)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::poisson_distribution<int> distribution(lambda);
	return distribution(generator);
}