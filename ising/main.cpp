/*
 * main.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Logger.h"

int main(int argc, char *argv[]) {
	// ./ising seed L beta
	int seed = 0;
	int L = 10;
	double beta = 0.2;
	if (argc == 4)
	{
		seed = std::stoi(argv[1]);
		L = std::stoi(argv[2]);
		beta = std::stod(argv[3]);
	}

	Logger log(seed,L);
	log.run_sim(beta);

}


