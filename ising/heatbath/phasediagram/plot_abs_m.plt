#==================================================
#         Author : Thomas Rometsch
#      Plot name : 2d Ising model phasediagram m
#==================================================

reset
clear

#==================================================
#             Definitions
#==================================================

writepdf = 0;

file1 = "results.txt"

label1 = "L=32"

output_name = "phasediagram.pdf"

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

set xlabel "{/Symbol b}"
set ylabel "h"
set zlabel "m"


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

unset key
set grid

set view map
set ylabel norotate offset -1,0

#set contour surf
splot file1 u 1:6:4 w pm3d


if (writepdf!=1) {
  pause -1
}
