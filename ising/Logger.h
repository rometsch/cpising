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
	int N_ac;			// Steps to destroy autocorrelation.
	int N_sweeps;		// Number of sweeps.
	int N_try;			// Number of tries for multihit.
	int seed;			// Seed for rng.

	double beta;
	std::vector<double> beta_log;
	std::vector<double> e_log;
	std::vector<double> m_log;
	std::vector<double> msq_log;
	std::vector<double> abs_m_log;
	std::vector<double> acc_rate_log;

	// Flags for printing out data.
	bool print;				// Print out data?
	bool dataformat;		// Use format for plotting?

	Logger(int L);
	virtual ~Logger();

	void sim_multihit(double beta);
	void calc_exact(double beta);

	void calc_data(double beta_min,double beta_max,int N,std::string method);

	void set_seed(int seed);
	void set_Ntry(int Ntry);
	void set_Ntherm(int Ntherm);
	void set_Nac(int Nac);
	void set_Nsweeps(int Nsweeps);
};

#endif /* LOGGER_H_ */
