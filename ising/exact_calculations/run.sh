#!/bin/bash
# Run calculations
../Release/cplab-ising-2dising config2.txt > exact2.txt
../Release/cplab-ising-2dising config3.txt > exact3.txt
../Release/cplab-ising-2dising config4.txt > exact4.txt

# Plot
gnuplot plot.plt
