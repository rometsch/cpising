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
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::run_sim(double beta) {

	//Clear the energy and magnetization vectors.
	this->e.clear();
	this->m.clear();

	// Update inverse temperature.
	this->beta = beta;
	this->lat->set_beta(beta);
	// Thermalize lattice.
	this->lat->sweep(this->N_therm);

	double acc_rate = 0;

	// Sweep some times.
	for (int n=0; n<this->N_sweeps; n++) {
		acc_rate += this->lat->sweep(N_a);
		this->e.push_back(this->lat->get_energy_density());
		this->m.push_back(this->lat->get_magnetization_density());
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double m_mean = 0;
	double abs_m_mean = 0;
	for (int i=0; i<this->N_sweeps; i++) {
		e_mean += this->e[i];
		m_mean += this->m[i];
		abs_m_mean += std::abs(this->m[i]);
	}

	e_mean *= 1./this->N_sweeps;
	m_mean *= 1./this->N_sweeps;
	abs_m_mean *= 1./this->N_sweeps;


	acc_rate *= 1./this->N_sweeps;
	std::cout << "beta = " << this->beta << std::endl;
	std::cout << "acc_rate = " << acc_rate << std::endl;
	std::cout << "<epsilon> = " << e_mean << std::endl;
	std::cout << "<m> = " << m_mean << std::endl;
	std::cout << "<|m|> = " << abs_m_mean << std::endl;
}

void Logger::calc_exact(double beta) {
	/* Calculate the system variables by averaging over all possible states.*/


	//Clear the energy and magnetization vectors.
	this->e.clear();
	this->m.clear();

	// Update inverse temperature.
	this->beta = beta;
	this->lat->set_beta(beta);

	// Sample all configurations.
	unsigned int N_configs = 2 << lat->L*lat->L;
	for (unsigned int conf=0; N_configs; conf++) {
		lat->set_configuration(conf);
		lat->calc_system_vars();
		this->e.push_back(this->lat->get_energy_density());
		this->m.push_back(this->lat->get_magnetization_density());
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double m_mean = 0;
	double abs_m_mean = 0;
	for (int i=0; i<N_configs; i++) {
		double weight = std::exp(-beta*e[i]);
		e_mean += weight*this->e[i];
		m_mean += weight*this->m[i];
		abs_m_mean += weight*std::abs(this->m[i]);
	}

	e_mean *= 1./N_configs;
	m_mean *= 1./N_configs;
	abs_m_mean *= 1./N_configs;


	std::cout << "beta = " << this->beta << std::endl;
	std::cout << "<epsilon> = " << e_mean << std::endl;
	std::cout << "<m> = " << m_mean << std::endl;
	std::cout << "<|m|> = " << abs_m_mean << std::endl;
}
