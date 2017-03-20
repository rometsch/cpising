#==================================================
#         Author : Thomas Rometsch
#      Plot name : 2d Ising find best Ntry
#==================================================

reset
clear

#==================================================
#             Definitions
#==================================================

writepdf = 0;

file1 = "result_a10.txt";
file2 = "result_a20.txt";
file3 = "result_a50.txt";
file4 = "result_a100.txt";
file5 = "result_c10.txt";
file6 = "result_c20.txt";
file7 = "result_c50.txt";
file8 = "result_c100.txt";

label1 = "a10";
label2 = "a20";
label3 = "a50";
label4 = "a100";
label5 = "c10";
label6 = "c20";
label7 = "c50";
label8 = "c100";

output_name = "plot_Ntry.pdf";

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

set style line 1 lt 1 ps 1 lc rgb "red" lw 1
set style line 2 lt 2 ps 1 lc rgb "orange" lw 1
set style line 3 lt 3 ps 1 lc rgb "#6495ED" lw 1
set style line 4 lt 4 lc rgb "black" lw 1
set style line 5 lt 5 lc rgb "forest-green" lw 1 ps 1

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
set ylabel "acceptance rate"
set key top right
unset yrange
plot  file1 u 1:6 ls 1 title label1, \
      file2 u 1:6 ls 2 title label2, \
      file3 u 1:6 ls 3 title label3, \
      file4 u 1:6 ls 4 title label4, \
      file5 u 1:6 ls 5 title label5, \
      file6 u 1:6 ls 6 title label6, \
      file7 u 1:6 ls 7 title label7, \
      file8 u 1:6 ls 8 title label8


set ylabel "Ntry"
set key top right
unset yrange
set logscale y
plot  file1 u 1:7 ls 1 title label1, \
      file2 u 1:7 ls 2 title label2, \
      file3 u 1:7 ls 3 title label3, \
      file4 u 1:7 ls 4 title label4, \
      file5 u 1:7 ls 5 title label5, \
      file6 u 1:7 ls 6 title label6, \
      file7 u 1:7 ls 7 title label7, \
      file8 u 1:7 ls 8 title label8

if (writepdf!=1) {
  pause -1
}
