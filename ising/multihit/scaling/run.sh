#!/bin/bash
# Run calculations
../../Release/cplab-ising-2dising 4sq_config.txt > 4sq_results.txt
../../Release/cplab-ising-2dising 8sq_config.txt > 8sq_results.txt
../../Release/cplab-ising-2dising 32sq_config.txt > 32sq_results.txt

# Plot
#gnuplot plot.plt
