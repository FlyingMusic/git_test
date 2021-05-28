#!/bin/python

num_array = [1, 2, 3, 4]

for i in num_array:
	for j in num_array:
		for k in num_array:
			if i!=j and i!=k and j!=k:
				print i,j,k

