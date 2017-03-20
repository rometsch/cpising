/*
 * Logger.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Logger.h"

Logger::Logger(int seed, int L) {
	// Initialize the lattice object and logger variables.

	this->N_therm = 10000;
	this->N_a = 10000;
	this->N_sweeps = 100;

	this->beta = 0.5;

	this->lat = new lattice(seed,L,1);

	// Flags for printing out data.
	print = true;			// Print out data?
	dataformat = true;		// Use format for plotting?
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::run_sim(double beta) {

	//Clear the energy and magnetization vectors.
	std::vector<double> e;
	std::vector<double> m;

	// Update inverse temperature.
	this->beta = beta;
	this->lat->set_beta(beta);
	// Thermalize lattice.
	this->lat->sweep(this->N_therm);

	double acc_rate = 0;

	// Sweep some times.
	for (int n=0; n<this->N_sweeps; n++) {
		acc_rate += this->lat->sweep(N_a);
		e.push_back(this->lat->get_energy_density());
		m.push_back(this->lat->get_magnetization_density());
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double m_mean = 0;
	double abs_m_mean = 0;
	for (int i=0; i<this->N_sweeps; i++) {
		e_mean += e[i];
		m_mean += m[i];
		abs_m_mean += std::abs(m[i]);
	}

	e_mean *= 1./this->N_sweeps;
	m_mean *= 1./this->N_sweeps;
	abs_m_mean *= 1./this->N_sweeps;
	acc_rate *= 1./this->N_sweeps;

	// Print out values.
	if (print) {
		if (dataformat) {
			std::cout << std::scientific
					<< beta << "\t"
					<< e_mean << "\t"
					<< m_mean << "\t"
					<< abs_m_mean << "\t"
					<< acc_rate
					<< std::endl;
		} else {
			std::cout << "beta = " << this->beta << std::endl;
			std::cout << "acc_rate = " << acc_rate << std::endl;
			std::cout << "<epsilon> = " << e_mean << std::endl;
			std::cout << "<m> = " << m_mean << std::endl;
			std::cout << "<|m|> = " << abs_m_mean << std::endl;
		}
	}
	// Store values in log vectors.
	beta_log.push_back(beta);
	e_log.push_back(e_mean);
	m_log.push_back(m_mean);
	abs_m_log.push_back(abs_m_mean);
	acc_rate_log.push_back(acc_rate);

}

void Logger::calc_exact(double beta) {
	/* Calculate the system variables by averaging over all possible states.*/
	//Clear the energy and magnetization vectors.
	std::vector<double> e;
	std::vector<double> m;

	// Update inverse temperature.
	this->beta = beta;
	this->lat->set_beta(beta);

	// Sample all configurations.
	int Lsq = lat->L*lat->L;
	unsigned int N_configs = 2 << (Lsq-1);
	for (unsigned int conf=0; conf < N_configs; conf++) {
	 	lat->set_configuration(conf);
		lat->calc_system_vars();
		e.push_back(this->lat->get_energy_density());
		m.push_back(this->lat->get_magnetization_density());
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double m_mean = 0;
	double abs_m_mean = 0;
	for (unsigned int i=0; i<N_configs; i++) {
		double weight = std::exp(-beta*e[i]);
		e_mean += weight*e[i];
		m_mean += weight*m[i];
		abs_m_mean += weight*std::abs(m[i]);
	}

//	e_mean *= 1./N_configs;
//	m_mean *= 1./N_configs;
//	abs_m_mean *= 1./N_configs;

	// Print out values.
	if (print) {
		if (dataformat) {
			std::cout << std::scientific
					<< beta << "\t"
					<< e_mean << "\t"
					<< m_mean << "\t"
					<< abs_m_mean
					<< std::endl;
		} else {
			std::cout << "beta = " << this->beta << std::endl;
			std::cout << "<epsilon> = " << e_mean << std::endl;
			std::cout << "<m> = " << m_mean << std::endl;
			std::cout << "<|m|> = " << abs_m_mean << std::endl;
		}
	}

	// Store values in log vectors.
	beta_log.push_back(beta);
	e_log.push_back(e_mean);
	m_log.push_back(m_mean);
	abs_m_log.push_back(abs_m_mean);

}

void Logger::calc_data(double beta_min,double beta_max,int N,std::string method) {
	/* Calculate the system variables for N values of beta between beta_min and beta_max using
	 * either the monte carlo method (method=mc)
	 * or the direct calculation (method=exact).
	 */

	std::cout << "# 2d Ising model" << std::endl;
	std::cout << "# L = " << lat->L << std::endl;
	std::cout << "# method = " << method << std::endl;
	if (method == "mc") {
		std::cout << "# beta \t e \t m \t |m| \t accRate" << std::endl;
	}
	if (method == "exact") {
		std::cout << "# beta \t e \t m \t |m|" << std::endl;
	}
	for (int i=0; i<N; i++) {
		double b = beta_min + 1.0*i/(N-1)*(beta_max-beta_min);
		if (method == "mc"){
			run_sim(b);
		}
		if (method == "exact") {
			calc_exact(b);
		}
	}
}
