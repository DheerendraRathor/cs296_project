#! /usr/bin/python3

import re
import os
import numpy
iteration = 500
rerun = 50

files=open("../data/g12_lab09data_01.csv","w")
files.write("")
files = open("../data/g12_lab09data_01.csv","a")
for i in range(1,iteration+1):
	for j in range(1,rerun+1):
		csv=""
		f = os.popen("../mybins/cs296_12_exe " + str(i))
		now = f.read()
		num=re.findall(r'[\d+.]+',now)
		num.insert(1,str(j))
		for k in range(len(num)-1):
			csv=csv + num[k] + ","
		csv+=num[6]
		csv+="\n"
		files.write(csv)

files = open("../data/g12_lab09data_01.csv","r")
test = files.readlines()
file1=open("../data/g12_lab09data_random.csv","w")
file1.write("")
file1=open("../data/g12_lab09data_random.csv","a")

for i in range(iteration):
	steprandarr=numpy.random.random_integers(0,rerun-1,15)
	for k in range(len(steprandarr)):
		temp=test[(i)*rerun + steprandarr[k]]
		file1.write(temp)
		
