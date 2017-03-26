#!/bin/bash
# Run calculations
../../Release/cplab-ising-2dising config_1.txt > results_1.txt
../../Release/cplab-ising-2dising config_2.txt > results_2.txt
../../Release/cplab-ising-2dising config_3.txt > results_3.txt

# Plot
#gnuplot plot.plt
