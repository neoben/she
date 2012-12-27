#!/usr/bin/env python

filename = './data/MSE.dat'
outfilename = './data/alpha_gamma_mse.dat'

# Read the MSE file line by line
input = open(filename,'r')
line = input.readlines()

# Write the alpha, gamma and MSE combination
output = open(outfilename,'a')

# Value to increase for the alpha and gamma parameters
step = 0.01

message = '\nATTENTION: the step parameter should have the same value as that of the "param_d.py" file.\n'
print message

value = step

alpha = []
gamma = []

# Create the list of parameters of the Double Exponential Smoothing Filter
while(value <= 0.9):
	alpha.append(value)
	gamma.append(value)
	value += step

l_int = []

# Convert the values of the file lines in integer values and put them in a list
for l in line:
	l_int.append(eval(l))

# Calculate the minimum MSE value
min_mse = min(l_int)

# Print the alpha and gamma value associated to the Minimum MSE
i = 0
for a in alpha:
	for g in gamma:
		output.write(str(a))
		output.write(" ")
		output.write(str(g))
		output.write(" ")
		output.write(str(l_int[i]))
		output.write('\n')
		if l_int[i] == min_mse:
			print '\n', 'alpha: ', a, ' | ', 'gamma: ', g, ' | ', 'Min MSE: ', min_mse, '\n'
		i += 1



