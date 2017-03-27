/*
 * main.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Logger.h"
#include <fstream>

double parse_parameter(std::ifstream &s);

int main(int argc, char *argv[]) {
	// ./ising seed L beta

	std::string config_filename = "ising_config.txt";
	if (argc>1) config_filename = argv[1];

	std::ifstream configfile;
	configfile.open(config_filename);


	int L = 2;
	double beta_min = 0.0;
	double beta_max = 1.0;
	double Npts = 11;
	std::string method = "mc";
	int seed = 0;
	int Ntry = 1;
	bool adaptive_multihit = true;
	bool output_thermalization_data = false;
	int Ntherm = 1000;
	int Nac = 100;
	int Nsweeps = 20;
	double h_min = 0.0;
	double h_max = 1.0;
	int N_pts_h = 1;

	L = parse_parameter(configfile);
	beta_min = parse_parameter(configfile);
	beta_max = parse_parameter(configfile);
	Npts = parse_parameter(configfile);
	std::getline(configfile,method);	// Read comment line.
	std::getline(configfile,method); 	// Repeat to read content.
	if (method!="exact") {
		seed = parse_parameter(configfile);
		Ntry = parse_parameter(configfile);
		adaptive_multihit = parse_parameter(configfile);
		Ntherm = parse_parameter(configfile);
		Nac = parse_parameter(configfile);
		Nsweeps = parse_parameter(configfile);
		output_thermalization_data = parse_parameter(configfile);
		if (method=="heatbath" or method=="heatbath_clean") {
			h_min = parse_parameter(configfile);
			h_max = parse_parameter(configfile);
			N_pts_h = parse_parameter(configfile);
		}
	}

	Logger log(L);
	if (method!="exact") {
		log.set_seed(seed);
		log.set_Ntry(Ntry);
		log.set_Ntherm(Ntherm);
		log.set_Nac(Nac);
		log.set_Nsweeps(Nsweeps);
		log.set_adaptive_multihit(adaptive_multihit);
		log.set_output_thermalization_data(output_thermalization_data);
	}
	log.calc_data(beta_min,beta_max,Npts,h_min,h_max,N_pts_h,method);
}


double parse_parameter(std::ifstream &s) {
	double param;
	std::string line;
	std::getline(s,line);
	if (line.at(0) == '#') {
		std::getline(s,line);
	}
	param = std::stod(line);
	return param;
}
