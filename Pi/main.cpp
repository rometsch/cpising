/*
 * main.cpp
 *
 *  Created on: Dec 15, 2015
 *      Author: thomas
 */

#include <random>
#include <iostream>
#include <fstream>
#include <cmath>

double approx_pi(int ndraws, int seed);

int main() {

	const int N_max = 1000000000;
	const int seed = 0;

	const double ref_pi = 3.141592653589793; // 15 decimals

	std::ofstream datafile;
	datafile.open("pi.txt");
	datafile << "# number of draws | approximation of pi | abs(approx - pi(15 decimals))" << '\n';


	for (int i=100; i<= N_max; i*=10) {
		double pi = approx_pi(i,seed);
		std::cout << "Pi = " << pi << " approximated with " << i << " draws." << std::endl;
		datafile << i << '\t' << pi << '\t' << std::abs(ref_pi - pi) << '\n';
	}

	datafile.close();
}

double approx_pi(int ndraws, int seed) {
	// Calculate Pi by drawing points from a unit square.

	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	generator.seed(seed);

	int ninside = 0;

	for (int i=0; i<ndraws; i++) {
		double x = distribution(generator);
		double y = distribution(generator);
		// If point is inside quarter of unit circle, increment count.
		if (x*x+y*y < 1) ninside++;
	}
	double pi = (double) ninside/ndraws*4;

	return pi;
}
