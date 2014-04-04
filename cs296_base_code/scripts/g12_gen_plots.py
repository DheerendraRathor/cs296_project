#! /usr/bin/python3

import pylab as pl
import numpy 
import re
import csv

iteration = 500
rerun = 50
test=""
data= open("../data/g12_lab09data_01.csv",'r')
test = data.readlines()
x = range(1,iteration+1)
ystep=[]
yloop=[]
ycollision=[]
yvelocity=[]
yposition=[]
ysum=[]
stepstd=[]
for i in range(iteration):
	step = 0
	loop=0
	collision=0
	velocity=0
	position=0
	tempstd=[]
	steprand=0
	for j in range(rerun):
		temp=test[(i)*(rerun)+j].split(',')
		tempstd.append(float(temp[2]))
		step+=float(temp[2])
		collision+=float(temp[3])
		velocity+=float(temp[4])
		position+=float(temp[5])
		loop+=float(temp[6])
	step = step/(rerun)
	loop = loop/(rerun)
	velocity/=(rerun)
	position/=(rerun)
	collision/=(rerun)
	stepstd.append(numpy.std(tempstd))
	ystep.append(step)
	yloop.append(loop)
	ycollision.append(collision)
	yvelocity.append(velocity)
	yposition.append(position)
	ysum.append(velocity+position+collision)

roll = 33
start=(roll-1)*rerun + 1
end=roll*rerun
rolly=[]
for i in range(start,end+1):
	temp=test[i].split(',')
	rolly.append(float(temp[2]))


filerand=open("../data/g12_lab09data_random.csv","r")
test=filerand.readlines()
ysteprand=[]
for k in range(iteration):
	steprand=0
	for l in range(15):
		temp=test[k*15 + l].split(',')
		steprand+=float(temp[2])
	ysteprand.append(steprand/15)
	

	

	
#print(stepstd[20],stepstd[21],stepstd[22],stepstd[23])
#print(ystep[20],ystep[21],ystep[22],ystep[23])
	
## Code for generating the first plot
maxima=max(yloop)
minima=min(yloop)
fig = pl.figure()
p1, = pl.plot(x, yloop,'r')
p2, = pl.plot(x,[maxima]*(iteration),'g--')
p3, = pl.plot(x,[minima]*(iteration),'c--')
p4 = pl.bar(x,ystep)
pl.legend([p1,p2,p3,p4],["Loop Time","Maxima of loop time","Minima of loop time","Step Time"],loc='best',prop={'size':8}) 
pl.xlabel("No. of Iterations")
pl.ylabel("Average time over the all reruns")
pl.title("Plot 1")
pl.grid()
pl.savefig("../plots/g12_plot01.png")

#Code for generating the Second plot
fig2 = pl.figure()
p1, = pl.plot(x,ycollision,'y')
p2, = pl.plot(x,yvelocity)
p3, = pl.plot(x,yposition)
p4, = pl.plot(x,ysum)
p5, = pl.plot(x,ystep)
pl.legend([p1,p2,p3,p4,p5],["Collision Time","Velocity Time","Position Time",
"Sum of collision,velocity and position","step Time"],loc='best',prop={'size':8})
pl.xlabel("No. of Iterations")
pl.ylabel("Average time over the all reruns")
pl.title("Plot 2")
pl.grid()
pl.savefig("../plots/g12_plot02.png")

#Code for generating Third Plot
fig3 = pl.figure()
p1 = pl.errorbar(x,ystep,yerr=stepstd,ecolor='r')
pl.legend([p1],["Error bar for Step Time"],loc='best',prop={'size':8})
pl.xlabel("No. of Iterations")
pl.ylabel("Average time over the all reruns")
pl.title("Plot 3")
pl.grid()
pl.savefig("../plots/g12_plot03.png")

#Code for generating the 4th plot
fig4 = pl.figure()
a,b,c=pl.hist(rolly,50,label="Frequeny Bar graph")
#pl.hist(rolly,50,cumulative=True,histtype='step',label="cumulative frequency graph")
d=[]
count=0
for i in range(len(a)):
	count+=a[i]
	d.append(count)
pl.plot(b[:-1],d,label="cumulative frequency")
pl.legend(loc='best',prop={'size':8})
pl.xlabel("Step Time for Roll No. 33")
pl.ylabel("Frequency of reruns")
pl.title("Plot 4")
pl.ylim([0,rerun+1])
pl.grid()
pl.savefig("../plots/g12_plot04.png")

#Code for generating the 5th plot
fig5 = pl.figure()
fit1 = pl.polyfit(x,ysteprand,1)
fit2 = pl.polyfit(x,ystep,1)
mb1 = pl.poly1d(fit1)
mb2 = pl.poly1d(fit2)
p1, = pl.plot(x,ysteprand,'.')
p2, = pl.plot(x,ystep,'.')
p3, = pl.plot(x,mb1(x))
p4, = pl.plot(x,mb2(x))
pl.grid()
pl.legend([p1,p2,p3,p4],["step time of random values","step time","Best fit line for random step values"
,"best fit line for step time"],loc='best',prop={'size':8})
pl.xlabel("No. of Iteration")
pl.ylabel("Average Time")
pl.title("Plot 5")
pl.savefig("../plots/g12_plot05.png")
