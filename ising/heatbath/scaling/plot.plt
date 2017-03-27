#==================================================
#         Author : Thomas Rometsch
#      Plot name : 2d Ising model scaling
#==================================================

reset
clear

#==================================================
#             Definitions
#==================================================

writepdf = 1;

file1 = "heatbath_scaling.txt"
file2 = "multihit_scaling.txt"
file3 = "single_flip_scaling.txt"

label1 = "heatbath"
label2 = "multihit"
label3 = "metropolis"

output_name = "scaling.pdf"

#==================================================
#             Set terminal
#==================================================

set term wxt enhanced
if (writepdf==1) {
  set term pdfcairo enhanced size 5.5in,4in dashed
  set output output_name
}

#==================================================
#             Style
#==================================================

set style line 1 lt 1 ps 0.5 lc rgb "red" lw 1
set style line 2 lt 2 ps 0.5 lc rgb "orange" lw 1
set style line 3 lt 4 ps 0.5 lc rgb "#6495ED" lw 1
set style line 4 lt 4 lc rgb "black" lw 1
set style line 5 lt 1 lc rgb "forest-green" lw 1 ps 1

#set format y "%2.1tx10^{%L}"
#==================================================
#             Axis Labels
#==================================================

set ylabel "e"
set xlabel "L"


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

set grid

#set xrange [0:0.26]

set multiplot layout 2,1

set ylabel "e"
#set yrange [-2.1:0.1]
set key center right box
plot  file1 u 1:2 title label1 ls 1 w lp, \
      file2 u 1:2 title label2 ls 2 w lp, \
      file3 u 1:2 title label3 ls 3 w lp, \
      e(0.4406868) title "analytical" ls 4


set ylabel "|m|"
set key center right box
unset yrange
plot  file1 u 1:4 title label1 ls 1 w lp, \
      file2 u 1:4 title label2 ls 2 w lp, \
      file3 u 1:4 title label3 ls 3 w lp, \
      abs_m(0.4406868) title "analytical" ls 4

#set ylabel "m^2"
#set yrange [0:0.8]
#set key center left
#plot  file1 u 1:5 title label1 ls 1 w lp, \
#      file2 u 1:5 title label2 ls 2 w lp, \
#      abs_m(0.4406868)*abs_m(0.4406868) title "analytical"

if (writepdf!=1) {
  pause -1
}
