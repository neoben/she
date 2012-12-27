#!/usr/bin/env python

import commands

message = '\nNOTE: use this script after the execution of the "var_window.py" script\n'
print message

# AP Parameters
curr_AP_id = 'AP0'
next_AP_id = 'AP1'

# DEWMA Parameters
alpha = 0.01
gamma = 0.001

message2 = '\nATTENTION: the alpha and gamma parameters should have the same values as those of the "var_window.py" script\n'
print message2

# Value to increase for the window
step = 2

message3 = '\nATTENTION: the step window parameter should have the same value as that of the "var_window.py" script\n'
print message3

# starting value of the window
value = 1

# Max value of the window
max_window = 95

# Output extension of the graphs (needed to the 'print.pl' script)
ptype = 'png'

window = []

# Create the list of window parameters
while(value <= max_window):
	window.append(value)
	value += step

# Execute the command for each value of window
for w in window:
	filename1 = curr_AP_id + '_for_a' + str(alpha) + '_g' + str(gamma) + '_w' + str(w) + '.dat'
	print1 = './print.pl ' + filename1 + ' -xrange [0:120] -yrange [0:70] -type ' + ptype + ' -output ' +  curr_AP_id + '_w' + str(w) + '.' + ptype
	commands.getstatusoutput(print1)
	
	filename2 = next_AP_id + '_for_a' + str(alpha) + '_g' + str(gamma) + '_w' + str(w) + '.dat'
	print2 = './print.pl ' + filename2 + ' -xrange [0:120] -yrange [0:70] -type ' + ptype + ' -output ' +  next_AP_id + '_w' + str(w) + '.' + ptype
	commands.getstatusoutput(print2)

	print3 =  './print.pl ' + filename1 + ' ' + filename2 + ' ' + ' -xrange [0:120] -yrange [0:70] -type ' + ptype + ' -output ' +  curr_AP_id + '_' + next_AP_id + '_w' + str(w) + '.' + ptype	
	commands.getstatusoutput(print3)	
