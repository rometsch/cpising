/*
 * Rng.cpp
 *
 *  Created on: Jan 6, 2016
 *      Author: thomas
 */

#include "Rng.h"


Rng::Rng(int seed) {
	// Initialize random number generator from std library to interval [0,1).
	 this->generator = new std::default_random_engine();
	 this->distribution = new std::uniform_real_distribution<double>(0.0,1.0);
	 this->generator->seed(seed);
	 this->seed = seed;
}
Rng::~Rng() {
	delete this->generator;
	delete this->distribution;
}

double Rng::draw() {
	// Return a random number from the interval [0,1).
	return this->distribution->operator() ( *(this->generator) );
}

double Rng::draw_between(double min, double max) {
	// Return a random number between min and max.
	double dist = max - min;
	double x = min + this->draw()*dist;
	return x;
}

double Rng::draw_between_int(int min, int max) {
	// Return an interger random number with minimum min and maximum max.
	if (min == max) return min;
	// First draw a random numbers uniformly from [0,1).
	double r = this->draw();
	// Calculate the number of parts to divide [0,1) into.
	int dist = max - min + 1;
	// Scale the random number, choose next lower interger and add to min.
	return min + (int) (r*dist);
}

int Rng::draw_spin() {
	// Return a random spin, either -1 or 1.
	int spin = 1;
	if (this->draw() < 0.5) {
		spin = -1;
	}
	return spin;
}

void Rng::reseed(int seed) {
	/* Reseed the rng */
	this->seed = seed;
	this->generator->seed(seed);
}
