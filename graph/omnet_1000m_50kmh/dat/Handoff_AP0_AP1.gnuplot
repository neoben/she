set terminal postscript eps enhanced color "Times-New-Roman" 18
set grid
set title "Hysteresis Handoff" font "Times-New-Roman,18'" tc lt 3
set output "handoff_ap0_ap1.eps"
set arrow from 74.8715,15 to 74.8715,60
plot  [0:100]  []  "AP0_smo.dat" title "AP0 smo"  with points ps 0.7 pt 1 lt 1 lc 1, "AP0_smo.dat" notitle with lines  lt 1 lc 1 , "AP1_smo.dat" title "AP1 smo"  with points ps 0.7 pt 2 lt 1 lc 2, "AP1_smo.dat" notitle with lines  lt 1 lc 2
