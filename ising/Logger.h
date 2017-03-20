/*
 * Logger.h
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <vector>
#include <iostream>
#include "lattice.h"

class Logger {
public:
	lattice* lat;
	int N_therm;		// Thermalization steps.
	int N_a;			// Steps to destroy autocorrelation.
	int N_sweeps;		// Number of sweeps.

	double beta;
	std::vector<double> beta_log;
	std::vector<double> e_log;
	std::vector<double> m_log;
	std::vector<double> abs_m_log;
	std::vector<double> acc_rate_log;

	// Flags for printing out data.
	bool print;				// Print out data?
	bool dataformat;		// Use format for plotting?

	Logger(int seed, int L);
	virtual ~Logger();

	void run_sim(double beta);
	void calc_exact(double beta);

	void calc_data(double beta_min,double beta_max,int N,std::string method);
};

#endif /* LOGGER_H_ */
