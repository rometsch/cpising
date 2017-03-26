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

file1 = "results_1.txt"
file2 = "results_2.txt"
file3 = "results_3.txt"
file4 = "results_4.txt"
file5 = "results_5.txt"
file6 = "results_6.txt"


output_name = "thermalization_heatbath.pdf";

#==================================================
#             Set terminal
#==================================================

set term wxt enhanced
if (writepdf==1) {
  set term pdfcairo enhanced size 7in,8in dashed
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

set multiplot layout 3,2

set title "{/Symbol b} = 0.2, h = 0"
set key center right
unset ylabel
plot [x=0:500] file1 u 1:2 every ::1 title "e", \
    file1 u 1:3 every ::1 title "m"


set title "{/Symbol b}=0.2, h = 1"
set key center right
unset ylabel
plot [x=0:500] file2 u 1:2 every ::1 title "e", \
    file2 u 1:3 every ::1 title "m"

set title "{/Symbol b} = 0.8, h = 0"
set key center right
unset ylabel
plot [x=0:2500] file3 u 1:2 every ::1 title "e", \
    file3 u 1:3 every ::1 title "m"


set title "{/Symbol b}=0.8, h = 1"
set key center right
unset ylabel
plot [x=0:2500] file4 u 1:2 every ::1 title "e", \
    file4 u 1:3 every ::1 title "m"

set title "{/Symbol b} = 0.4406868, h = 0"
set key center right
unset ylabel
plot [x=0:2500] file5 u 1:2 every ::1 title "e", \
    file5 u 1:3 every ::1 title "m"


set title "{/Symbol b}=0.4406868, h = 1"
set key center right
unset ylabel
plot [x=0:2500] file6 u 1:2 every ::1 title "e", \
    file6 u 1:3 every ::1 title "m"




if (writepdf!=1) {
  pause -1
}
