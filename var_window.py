#!/usr/bin/env python

import commands

message = '\nIMPORTANT: check that the variable "use_window" of the "src/prediction_d.cpp" is set to TRUE\n'
print message

cmd = './bin/shs_d_choose'

# AP Parameters
curr_AP_id = 'AP0'
next_AP_id = 'AP1'
curr_AP_data = './data/ap0.dat'
next_AP_data = './data/ap1.dat'

# DEWMA Parameters
alpha = 0.01
gamma = 0.001

# Value to increase for the window
step = 2

# Starting value of the window
value = 1

# Max value of the window
max_window = 95

window = []

# Create the list of window parameters
while(value <= max_window):
	window.append(value)
	value += step

# Execute the command for each value of window
for w in window:
	tot = cmd + ' ' + curr_AP_id + ' ' + next_AP_id + ' ' + curr_AP_data + ' ' + next_AP_data + ' ' + str(alpha) + ' ' + str(gamma) + ' ' + str(w)
	commands.getstatusoutput(tot)
	
