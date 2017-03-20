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
	int seed = 0;
	std::string method = "mc";

	L = parse_parameter(configfile);
	beta_min = parse_parameter(configfile);
	beta_max = parse_parameter(configfile);
	Npts = parse_parameter(configfile);
	seed = parse_parameter(configfile);
	std::getline(configfile,method);	// Read comment line.
	std::getline(configfile,method); 	// Repeat to read content.

	Logger log(seed,L);
	log.calc_data(beta_min,beta_max,Npts,method);
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
