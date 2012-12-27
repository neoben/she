#!/usr/bin/env python

import commands

message = '\nREMEMBER: delete the file <./data/MSE.dat> if you are running a new analysis phase for the alpha and gamma parameters!\n'
print message

cmd = './bin/shs_d_choose'

# AP Parameters
curr_AP_id = 'AP1'
next_AP_id = 'AP2'
curr_AP_data = './data/ap1.dat'
next_AP_data = './data/ap2.dat'

message2 = '\nNOTE: if you need to use the Window Parameter set the variable "use_window" of the "src/prediction_d.cpp" file to TRUE\n'

# Window size
window = 30

# Value to increase for alpha and gamma paramteres
step = 0.01

value = step

alpha = []
gamma = []

# Create the list of parameters of the Double Exponential Smoothing Filter
while(value <= 0.9):
	alpha.append(value)
	gamma.append(value)
	value += step

# Execute the command for each combination of the alpha and gamma parameters
for a in alpha:
	for g in gamma:
		tot = cmd + ' ' + curr_AP_id + ' ' + next_AP_id + ' ' + curr_AP_data + ' ' + next_AP_data + ' ' + str(a) + ' ' + str(g) + ' ' + str(window)
		commands.getstatusoutput(tot)


