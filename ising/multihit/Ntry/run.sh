#!/bin/bash
# Run calculations
../../Release/cplab-ising-2dising config_a10.txt > result_a10.txt
../../Release/cplab-ising-2dising config_a20.txt > result_a20.txt
../../Release/cplab-ising-2dising config_a50.txt > result_a50.txt
../../Release/cplab-ising-2dising config_a100.txt > result_a100.txt
../../Release/cplab-ising-2dising config_c10.txt > result_c10.txt
../../Release/cplab-ising-2dising config_c20.txt > result_c20.txt
../../Release/cplab-ising-2dising config_c50.txt > result_c50.txt
../../Release/cplab-ising-2dising config_c100.txt > result_c100.txt

# Plot
gnuplot plot.plt
