/*
 * main.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Logger.h"

int main(int argc, char *argv[]) {
	// ./ising seed L beta
	int seed = std::stoi(argv[1]);
	int L = std::stoi(argv[2]);
	double beta = std::stod(argv[3]);

	Logger log(seed,L);
	log.run_sim(beta);

}


