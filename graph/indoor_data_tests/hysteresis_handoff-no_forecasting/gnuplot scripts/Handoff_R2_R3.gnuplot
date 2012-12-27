set terminal postscript eps enhanced color "Times-New-Roman" 18
set grid
set title "Hysteresis Handoff" font "Times-New-Roman,18'" tc lt 3
set output "handoff_r2_r3.eps"
set arrow from 65.2602,15 to 65.2602,50
set arrow from 86.3103,15 to 86.3103,50
set arrow from 134.001,15 to 134.001,50
set arrow from 154.902,15 to 154.902,50
set arrow from 204.491,15 to 204.491,50
set arrow from 222.123,15 to 222.123,50
plot  [0:250]  []  "R2_smo.dat" title "R2 smo"  with points ps 0.7 pt 1 lt 1 lc 1, "R2_smo.dat" notitle with lines  lt 1 lc 1 , "R3_smo.dat" title "R3 smo"  with points ps 0.7 pt 2 lt 1 lc 2, "R3_smo.dat" notitle with lines  lt 1 lc 2
