#==================================================
#         Author : Thomas Rometsch
#      Plot name : 2d Ising model exact calculations
#==================================================

reset
clear

#==================================================
#             Definitions
#==================================================

writepdf = 1;

file1 = "results_pos.txt"
file2 = "results_neg.txt"
file3 = "results_pos_32.txt"
file4 = "results_neg_32.txt"



label1 = "L=8, pos"
label2 = "L=8, neg"
label3 = "L=32, pos"
label4 = "L=32, neg"

output_name = "hysteresis.pdf"

#==================================================
#             Set terminal
#==================================================

set term wxt enhanced
if (writepdf==1) {
  set term pdfcairo enhanced size 7in,4in dashed
  set output output_name
}

#==================================================
#             Style
#==================================================

set style line 1 lt 1 ps 1 lc rgb "red" lw 1
set style line 2 lt 3 ps 1 lc rgb "orange" lw 1
set style line 3 lt 2 ps 1 lc rgb "#6495ED" lw 1
set style line 4 lt 4 ps 1 lc rgb "black" lw 1
set style line 5 lt 1 lc rgb "forest-green" lw 1 ps 1

#set format y "%2.1tx10^{%L}"
#==================================================
#             Axis Labels
#==================================================

set ylabel "m"
set xlabel "h"


#==================================================
#             Analytic Functions
#==================================================
xi(x) = 2*tanh(2*x)/cosh(2*x);
e(x) = - 1/tanh(2*x) * ( 1 + ( 2*tanh(2*x)**2 - 1 )*(2/pi)*EllipticK(xi(x)) );
abs_m(x) = (1 - sinh(2*x)**-4)**(1./8);

set samples 100000

#==================================================
#             Plot
#==================================================


set key bottom right
set yrange [-1.1:1.1]
plot  file1 u 6:3 title label1 ls 1 w lp, \
    file2 u 6:3 title label2 ls 2 w lp, \
    file3 u 6:3 title label3 ls 3 w lp, \
    file4 u 6:3 title label4 ls 4 w lp



if (writepdf!=1) {
  pause -1
}
