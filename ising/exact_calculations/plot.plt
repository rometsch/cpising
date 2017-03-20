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

file1 = "exact2.txt"
file2 = "exact3.txt"
file3 = "exact4.txt"

label1 = "L=2"
label2 = "L=3"
label3 = "L=4"

output_name = "plot_exact_vs_ana.pdf"

#==================================================
#             Set terminal
#==================================================

set term qt enhanced
if (writepdf==1) {
  set term pdfcairo enhanced size 7in,4in dashed
  set output output_name
}

#==================================================
#             Style
#==================================================

set style line 1 lt 7 ps 0.3 lc rgb "red" lw 1
set style line 2 lt 7 ps 0.3 lc rgb "orange" lw 1
set style line 3 lt 7 ps 0.3 lc rgb "#6495ED" lw 1
set style line 4 lt 4 lc rgb "black" lw 1
set style line 5 lt 1 lc rgb "forest-green" lw 1 ps 1

#set format y "%2.1tx10^{%L}"
#==================================================
#             Axis Labels
#==================================================

set ylabel "e"
set xlabel "{/Symbol b}"


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


set multiplot layout 1,2
set ylabel "e"
set key top right
set yrange [-2:0]
plot  file1 u 1:2 title label1 ls 1 w p, \
      file2 u 1:2 title label2 ls 2 w p, \
      file3 u 1:2 title label3 ls 3 w p, \
      e(x) title "e({/Symbol b})" ls 4 w l



set ylabel "|m|"
set key bottom right
unset yrange
plot  file1 u 1:4 title label1 ls 1 w p, \
      file2 u 1:4 title label2 ls 2 w p, \
      file3 u 1:4 title label3 ls 3 w p, \
      abs_m(x) title "|m|({/Symbol b})" ls 4 w l

if (writepdf!=1) {
  pause -1
}
