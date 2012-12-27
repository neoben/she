set terminal postscript eps enhanced color "Times-New-Roman" 18
set grid
set title "Hysteresis Handoff" font "Times-New-Roman,18'" tc lt 3
set output "handoff_r3_r4.eps"
set arrow from 3.28983,15 to 3.28983,50
set arrow from 57.1302,15 to 57.1302,50
set arrow from 93.5413,15 to 93.5413,50
set arrow from 126.222,15 to 126.222,50
set arrow from 160.951,15 to 160.951,50
set arrow from 195.771,15 to 195.771,50
set arrow from 227.981,15 to 227.981,50
plot  [0:250]  []  "R3_smo.dat" title "R3 smo"  with points ps 0.7 pt 1 lt 1 lc 1, "R3_smo.dat" notitle with lines  lt 1 lc 1 , "R4_smo.dat" title "R4 smo"  with points ps 0.7 pt 2 lt 1 lc 2, "R4_smo.dat" notitle with lines  lt 1 lc 2
