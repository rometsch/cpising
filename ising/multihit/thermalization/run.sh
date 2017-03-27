#!/bin/bash
# Run calculations
../../Release/cplab-ising-2dising test1_config.txt > result1.txt
../../Release/cplab-ising-2dising test2_config.txt > result2.txt
../../Release/cplab-ising-2dising test3_config.txt > result3.txt

# Plot
#gnuplot plot.plt
