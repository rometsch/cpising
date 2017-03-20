#==================================================
#         Author : Thomas Rometsch
#      Plot name : logscale analysis of damping rates
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

output_name = "exact_calculations.pdf"

#==================================================
#             Set terminal
#==================================================

set term qt enhanced
if (writepdf==1) {
  set term pdfcairo enhanced size 7in,5in dashed
  set output output_name
}
#set border lw 2
#set grid lw 2 dt "-"


#==================================================
#             Style
#==================================================

set style line 1 lt 1 lc rgb "black" lw 1 ps 1
set style line 2 lt 2 lc rgb "orange" lw 1
set style line 3 lt 3 lc rgb "#6495ED" lw 1
set style line 4 lt 4 lc rgb "red" lw 1
set style line 5 lt 1 lc rgb "forest-green" lw 1 ps 1

#set format y "%2.1tx10^{%L}"
#==================================================
#             Axis Labels
#==================================================

set ylabel "e"
set xlabel "{/Symbol b}"

#==================================================
#             Plot
#==================================================


set multiplot layout 1,2
set ylabel "e"
set key bottom left
plot  file1 u 1:2 title label1 ls 1 w p, \
      file2 u 1:2 title label2 ls 2 w p, \
      file3 u 1:2 title label3 ls 3 w p



set ylabel "|m|"
set key top left
plot  file1 u 1:4 title label1 ls 1 w p, \
      file2 u 1:4 title label2 ls 2 w p, \
      file3 u 1:4 title label3 ls 3 w p


if (writepdf!=1) {
  pause -1
}
