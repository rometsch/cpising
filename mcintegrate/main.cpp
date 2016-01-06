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

class rng {
	// Wrapper for the std::random uniform rng.
public:
	int seed;
	std::default_random_engine* generator;
	std::uniform_real_distribution<double>* distribution;

	rng(int seed) {
		// Initialize random number generator from std library to interval [0,1).
		 this->generator = new std::default_random_engine();
		 this->distribution = new std::uniform_real_distribution<double>(0.0,1.0);
		 this->generator->seed(seed);
		 this->seed = seed;
	}
	virtual ~rng() {
		delete this->generator;
		delete this->distribution;
	}

	double draw() {
		// Return a random number from the interval [0,1).
		return this->distribution->operator() ( *(this->generator) );
	}

	double draw_between(double min, double max) {
		// Return a random number between min and max.
		double dist = max - min;
		double x = min + this->draw()*dist;
		return x;
	}
};

class normaldist {
	// Class for normal distribution number generator.
	// Using Metropolis algorithm.
public:
	int seed;
	rng* Rng;
	double x;
	double mu;
	double sigma;

	// For probability calculation.
	double prefactor;
	double two_sigma_sq;

	// Monte Carlo parameter
	int N_therm;
	int N_ac;

	normaldist(int seed, double mu, double sigma, int N_therm, int N_ac) {
		// Initialize the generator.

		this->seed = seed;			// Save seed.
		this->Rng = new rng(seed);	// Create an object of the uniform rng.
		this->x = mu;				// Initialize x with mu.
		this->sigma = sigma;		// Save the width sigma.
		this->mu = mu;				// Save the mean mu.

		this->N_therm = N_therm;	// Number of thermalisation steps.
		this->N_ac = N_ac;			// Number of steps to go for each draw. ac = autocorrelation

		// Calculate prefactor for probability density function.
		this->two_sigma_sq = 2*this->sigma*this->sigma;
		this->prefactor = 1/this->sigma/std::sqrt(2*M_PI);

		// Thermalize the Markov-Chain.
		for (int i=0; i<this->N_therm; i++) this->Metropolis_step();
	}

	virtual ~normaldist() {
		delete this->Rng;
	}

	double draw() {
		// Draw a random number from the normal distribution.
		// Do N_ac Metropolis steps to destroy autocorrelation.
		for (int i=0; i<this->N_ac; i++) this->Metropolis_step();
		// Return the state of the Markov-Chain.
		return this->x;
	}

	void Metropolis_step() {
		double x = this->x;				// Old state.
		double y = 0;					// New state.
		double p_old = 0, p_new = 0;	// Probability of old and new state.
		double P = 0;					// Ratio of old an new state.

		// 1. Propose a change.
		y = this->x + this->Rng->draw_between(-1,1);

		// 2. Calculate probabiliy of old state and new state and then ccalculate the ratio R.
		p_old = this->p(x);
		p_new = this->p(y);
		P = p_new/p_old;

		// 3. Accept the change if P>1.
		if (P >= 1) {
			this->x = y;	// Update the state variable.
		} else {
		// 4. If P<1 accept with probability P.
			if (this->Rng->draw() < P) {
				// Accept the change
				this->x = y;	// Update the state variable.
			}
			// 5. Otherwise pick the old state as new state, i.e. do nothing.
		}
	}

	double p(double x) {
		// Probability density function for normal distribution.
		double p = 0;
		p = this->prefactor*std::exp(-(x-this->mu)*(x-this->mu)/this->two_sigma_sq);
		return p;
	}
};


double func_to_integrate(double x) {
	// The function to integrate.
	return std::exp(-(x*x)/2);
}

int main(int argc, char* argv[]) {

	// Get the number of draws from the command line arguments.
	int N = 100000;
	if (argc == 2) N = std::stoi(argv[1]);

	// Calculate the integral
	// Set mean to 0.
	// Set sigma to
	normaldist Normal(0, 0 , 1, 1000, 100);

//	std::cout << Normal.prefactor << std::endl;


	double I = 0;

	for (int i=0; i<N ; i++) {
		double x = Normal.draw();
//		std::cout << x << std::endl;
		I += func_to_integrate(x)/Normal.p(x);
	}
	I = I/N;
	std::cout << "I = " << I << std::endl;
}
