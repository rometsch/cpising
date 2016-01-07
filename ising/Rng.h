/*
 * Rng.h
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#ifndef RNG_H_
#define RNG_H_

#include <random>

class Rng {
	// Wrapper for the std::random uniform rng.
public:
	int seed;
	std::default_random_engine* generator;
	std::uniform_real_distribution<double>* distribution;

	Rng(int seed);
	virtual ~Rng();

	double draw();									// Return a random number from the interval [0,1).
	double draw_between(double min, double max);	// Return a random number between min and max.
	double draw_between_int(int min, int max);		// Return an interger random number with minimum min and maximum max.
	int draw_spin();								// Return a random spin, either -1 or 1.
};
#endif /* RNG_H_ */
