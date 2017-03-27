#==================================================
#         Author : Thomas Rometsch
#      Plot name : 2d Ising find best Ntry
#==================================================

reset
clear

#==================================================
#             Definitions
#==================================================

writepdf = 1;

file1 = "result1.txt"
file2 = "result2.txt"
file3 = "result3.txt"

output_name = "thermalization_multihit.pdf";

#==================================================
#             Set terminal
#==================================================

if (writepdf!=1) {
  set term wxt enhanced
}
if (writepdf==1) {
  set term pdfcairo enhanced size 7in,6in dashed
  set output output_name
}

#==================================================
#             Style
#==================================================

set style line 1 lt 1 ps 0.3 lc rgb "black" lw 1
set style line 2 lt 2 ps 0.3 lc rgb "orange" lw 1
set style line 3 lt 3 ps 0.3 lc rgb "#6495ED" lw 1
set style line 4 lt 4 lc rgb "black" lw 1
set style line 5 lt 5 lc rgb "forest-green" lw 1 ps 1

#set format y "%2.1tx10^{%L}"
#==================================================
#             Axis Labels
#==================================================

set ylabel "e"
set xlabel "N_{therm}"
set xtics rotate by -45

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

while (1)  {
  if (writepdf==0) {clear}
  set multiplot layout 2,3 columnsfirst

  set title "{/Symbol b} = 0.8"
  set key top right
  unset ylabel
  plot [x=0:500] file1 u 1:2 ls 3 title "e", \
      file1 u 1:3 ls 2 title "m"
  set ylabel "acceptance rate"
  plot [x=0:500] file1 u 1:4 ls 3 notitle


  set title "{/Symbol b}=0.4406868"
  set key top left
  unset ylabel
  plot file2 u 1:2 ls 3 title "e", \
      file2 u 1:3 ls 2 title "m"
  set ylabel "acceptance rate"
  plot file2 u 1:4 ls 3 notitle


  set title "{/Symbol b}=0.2"
  set key top left
  unset ylabel
  plot [x=0:500] file3 u 1:2 ls 3 title "e", \
      file3 u 1:3 ls 2 title "m"
  set ylabel "acceptance rate"
  plot [x=0:500] file3 u 1:4 ls 3 notitle


  if (writepdf==1) {
    exit
  }

  pause 2
}

if (writepdf!=1) {
  pause -1
}
