/*
 * Logger.h
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <vector>
#include "lattice.h"

class Logger {
public:
	lattice* lat;
	int N_therm;		// Thermalization steps.
	int N_a;			// Steps to destroy autocorrelation.
	int N_sweeps;		// Number of sweeps.

	double beta;
	std::vector<double> e;
	std::vector<double> m;

	Logger(int seed, int L);
	virtual ~Logger();

	void run_sim(double beta);
};

#endif /* LOGGER_H_ */
