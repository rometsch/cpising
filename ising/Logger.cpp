/*
 * Logger.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Logger.h"

Logger::Logger(int L) {
	// Initialize the lattice object and logger variables.

	// Initalize iteration numbers to some defaults.
	// They should be set later again using values from the configuration file.
	this->N_therm = 10000;
	this->N_ac = 10000;
	this->N_sweeps = 100;
	this->N_try = 20;

	this->adaptive_multihit = true;
	this->output_thermalization_data = false;;

	this->seed = 0;

	this->lat = new lattice(L,1);

	// Flags for printing out data.
	print = true;			// Print out data?
	dataformat = true;		// Use format for plotting?
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::sim_multihit(double beta) {

	//Clear the energy and magnetization vectors.
	std::vector<double> e;
	std::vector<double> m;

	int Ntry = this->N_try;

	// Thermalize lattice.
	double current_acc_rate = 0;
	for (int n=0; n<N_therm; n++) {
		current_acc_rate = this->lat->sweep_multihit(beta, Ntry);
		if (adaptive_multihit) Ntry = adjust_Ntry(current_acc_rate,Ntry);
		if (output_thermalization_data) {
			std::cout << std::scientific
					<< n << "\t"
					<<lat->get_energy_density() << "\t"
					<< lat->get_magnetization_density() << "\t"
					<< current_acc_rate << "\t"
					<< Ntry
					<< std::endl;
		}
	}

	double acc_rate = 0;

	// Sweep some times.
	for (int n=0; n<this->N_sweeps*N_ac; n++) {
		current_acc_rate = this->lat->sweep_multihit(beta, Ntry);
		if (adaptive_multihit) Ntry = adjust_Ntry(current_acc_rate,Ntry);
		if (n%N_ac == 0) {
			acc_rate += current_acc_rate;
			e.push_back(this->lat->get_energy_density());
			m.push_back(this->lat->get_magnetization_density());
		}
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double esq_mean = 0;
	double m_mean = 0;
	double msq_mean = 0;
	double abs_m_mean = 0;
	for (int i=0; i<this->N_sweeps; i++) {
		e_mean += e[i];
		esq_mean += e[i]*e[i];
		m_mean += m[i];
		msq_mean += m[i]*m[i];
		abs_m_mean += std::abs(m[i]);
	}

	e_mean *= 1./this->N_sweeps;
	esq_mean *= 1./this->N_sweeps;
	m_mean *= 1./this->N_sweeps;
	msq_mean *= 1./this->N_sweeps;
	abs_m_mean *= 1./this->N_sweeps;
	acc_rate *= 1./this->N_sweeps;
	double cV = beta*beta*(esq_mean-e_mean*e_mean);

	// Print out values.
	if (print and !output_thermalization_data) {
		if (dataformat) {
			std::cout << std::scientific
					<< beta << "\t"
					<< e_mean << "\t"
					<< m_mean << "\t"
					<< abs_m_mean << "\t"
					<< msq_mean << "\t"
					<< acc_rate << "\t"
					<< Ntry << "\t"
					<< cV
					<< std::endl;
		} else {
			std::cout << "beta = " << beta << std::endl;
			std::cout << "acc_rate = " << acc_rate << std::endl;
			std::cout << "<epsilon> = " << e_mean << std::endl;
			std::cout << "<m> = " << m_mean << std::endl;
			std::cout << "<|m|> = " << abs_m_mean << std::endl;
			std::cout << "<msq> = " << msq_mean << std::endl;
		}
	}
	// Store values in log vectors.
	beta_log.push_back(beta);
	e_log.push_back(e_mean);
	m_log.push_back(m_mean);
	msq_log.push_back(msq_mean);
	abs_m_log.push_back(abs_m_mean);
	acc_rate_log.push_back(acc_rate);
}

void Logger::sim_heatbath(double beta, double h) {

	// Initialize energy and magnetization vectors.
	std::vector<double> e;
	std::vector<double> m;

	// Thermalize lattice.
	for (int n=0; n<N_therm; n++) {
		this->lat->sweep_heatbath(beta,h);
		if (output_thermalization_data) {
			lat->calc_system_vars();
			std::cout << std::scientific
					<< n << "\t"
					<<lat->get_energy_density() << "\t"
					<< lat->get_magnetization_density() << "\t"
					<< std::endl;
		}
	}

	// Sweep some times.
	for (int n=0; n<this->N_sweeps*N_ac; n++) {
		this->lat->sweep_heatbath(beta,h);
		if (n%N_ac == 0) {
			this->lat->calc_system_vars();
			e.push_back(this->lat->get_energy_density());
			m.push_back(this->lat->get_magnetization_density());
		}
	}

	// Calulate means of energy and magnetization.
	double e_mean = 0;
	double esq_mean = 0;
	double m_mean = 0;
	double msq_mean = 0;
	double abs_m_mean = 0;
	for (int i=0; i<this->N_sweeps; i++) {
		e_mean += e[i];
		esq_mean += e[i]*e[i];
		m_mean += m[i];
		msq_mean += m[i]*m[i];
		abs_m_mean += std::abs(m[i]);
	}

	e_mean *= 1./this->N_sweeps;
	esq_mean *= 1./this->N_sweeps;
	m_mean *= 1./this->N_sweeps;
	msq_mean *= 1./this->N_sweeps;
	abs_m_mean *= 1./this->N_sweeps;
	double cV = beta*beta*(esq_mean-e_mean*e_mean);

	// Print out values.
	if (print and !output_thermalization_data) {
		if (dataformat) {
			std::cout << std::scientific
					<< beta << "\t"
					<< e_mean << "\t"
					<< m_mean << "\t"
					<< abs_m_mean << "\t"
					<< msq_mean << "\t"
					<< h << "\t"
					<< "\t"
					<< cV
					<< std::endl;
		} else {
			std::cout << "beta = " << beta << std::endl;
			std::cout << "<epsilon> = " << e_mean << std::endl;
			std::cout << "<m> = " << m_mean << std::endl;
			std::cout << "<|m|> = " << abs_m_mean << std::endl;
			std::cout << "<msq> = " << msq_mean << std::endl;
		}
	}
	// Store values in log vectors.
	beta_log.push_back(beta);
	e_log.push_back(e_mean);
	m_log.push_back(m_mean);
	msq_log.push_back(msq_mean);
	abs_m_log.push_back(abs_m_mean);
}


void Logger::calc_exact(double beta) {
	/* Calculate the system variables by averaging over all possible states.*/
	//Clear the energy and magnetization vectors.
	std::vector<double> e;
	std::vector<double> m;

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
	double Z = 0;
	double e_mean = 0;
	double m_mean = 0;
	double abs_m_mean = 0;
	for (unsigned int i=0; i<N_configs; i++) {
		double weight = std::exp(-beta*e[i]*Lsq);
		Z += weight;
		e_mean += weight*e[i];
		m_mean += weight*m[i];
		abs_m_mean += weight*std::abs(m[i]);
	}

	e_mean *= 1./Z;
	m_mean *= 1./Z;
	abs_m_mean *= 1./Z;

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
			std::cout << "beta = " << beta << std::endl;
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

void Logger::calc_data(double beta_min,double beta_max,int N_pts_beta, double h_min, double h_max, int N_pts_h,std::string method) {
	/* Calculate the system variables for N values of beta between beta_min and beta_max using
	 * either the mutlihit method (method="multihit")
	 * or the direct calculation (method="exact").
	 */

	std::cout << "# 2d Ising model" << std::endl;
	std::cout << "# L = " << lat->L << std::endl;
	std::cout << "# method = " << method << std::endl;
	std::cout << "# beta_min = " << beta_min << std::endl;
	std::cout << "# beta_max = " << beta_max << std::endl;
	std::cout << "# N_pts_beta = " << N_pts_beta << std::endl;
	std::cout << "# h_min = " << h_min << std::endl;
	std::cout << "# h_max = " << h_max << std::endl;
	std::cout << "# N_pts_h = " << N_pts_h << std::endl;
	if (method != "exeact") {
		std::cout << "# Ntherm = " << N_therm << std::endl;
		std::cout << "# Nac = " << N_ac << std::endl;
		std::cout << "# Number of datapoints = " << N_sweeps << std::endl;
	}
	if (method == "multihit") {
		std::cout << "# beta \t e \t m \t |m| \t msq \t accRate \t Ntry \t cV" << std::endl;
	}
	if (method == "heatbath") {
		std::cout << "# beta \t e \t m \t |m| \t msq \t h \t - \t cV" << std::endl;
		}
	if (method == "exact") {
		std::cout << "# beta \t e \t m \t |m|" << std::endl;
	}
	for (int i=0; i<N_pts_beta; i++) {
		for (int j=0; j<N_pts_h; j++) {
			double b = beta_min;
			double h = h_min;
			if (N_pts_beta>1) {
				b = beta_min + 1.0*i/(N_pts_beta-1)*(beta_max-beta_min);
			}
			if (N_pts_h>1) {
				h = h_min + 1.0*j/(N_pts_h-1)*(h_max-h_min);
			}
			if (method == "multihit"){
				sim_multihit(b);
			}
			if (method == "heatbath"){
				sim_heatbath(b,h);
			}
			if (method == "exact") {
				calc_exact(b);
			}
		}
	}
}


void Logger::set_seed(int seed) {
	/* Set the seed of the rng of the lattice object. */
	this->seed = seed;
	this->lat->set_seed(seed);
}

void Logger::set_Ntry(int Ntry) {
	/* Set number of tries for multihit algorithm. */
	this->N_try = Ntry;
}

void Logger::set_Ntherm(int Ntherm) {
	/* Set number of thermalization steps. */
	this->N_therm = Ntherm;
}

void Logger::set_Nac(int Nac) {
	/* Set number of steps to destroy auto correlation. */
	this->N_ac = Nac;
}

void Logger::set_Nsweeps(int Nsweeps) {
	/* Set number of steps to sweep for each configuration. */
	this->N_sweeps = Nsweeps;
}

void Logger::set_adaptive_multihit(bool adaptive_multihit) {
	this->adaptive_multihit = adaptive_multihit;
}

void Logger::set_output_thermalization_data(bool output_thermalization_data) {
	this->output_thermalization_data = output_thermalization_data;
}


int Logger::adjust_Ntry(double acc_rate, int Ntry) {
	/* Adjust Ntry to obtain acceptance rate of 0.5. */
	int Nnew = Ntry;
	double desired_acc_rate = 0.5;
	double delta = acc_rate - desired_acc_rate;		// Current acc rate - desired acc rate.
	if (delta > 0) Nnew = Ntry +1;
	if (delta < 0) Nnew = Ntry -1;
	// Adjust to the interval [0.1,10]*initial Ntry
	if (Nnew > 10*N_try) Nnew = 10*N_try;
	if (Nnew < 0.1*N_try) Nnew = 0.1*N_try;
//	std::cout << "acc_rate = " << acc_rate << "\t Ntry = " << Ntry << "\t Nnew = " << Nnew << std::endl;
	return Nnew;
}
