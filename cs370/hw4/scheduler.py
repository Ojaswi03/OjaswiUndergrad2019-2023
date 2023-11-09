import csv
import sys

class P:
    def __init__(self, processes, arrival_time, burst_time, priority):
        self.process = int (processes)
        self.arrival = int (arrival_time)
        self.burst = int (burst_time)
        self.priority = int (priority)
        self.waitT = 0
        self.turnAT = 0
        self.totalwait = 0
        self.totaltat = 0
        self.quantum = 0
        self.exit = 0

print("--------------------FCFS----------------------\n")
curr_time = 0
process = []
## Reading from a CSV file 
with open(sys.argv[1], 'r') as csvfile:
    reader = csv.reader(csvfile, skipinitialspace=True)
    linecount = 0
    for row in reader:
        if linecount == 0:
            linecount += 1
        else:
            process.append(P(row[0], row[1],row[2],row[3]))

gantt_chart = []
process.sort(key = lambda x: (x.arrival, x.process)) ## sorting first with arrival and the with PID
str = ""
for i in process: ## Making a gantt chart 
    if (curr_time < i.arrival):
        str = "[{0}-{1}] Process {2}" .format(curr_time, i.arrival, 'IDLE')
        gantt_chart.append(str)
    if (curr_time > i.arrival):
        str = "[{0}-{1}] Process {2}" .format(curr_time, curr_time+ i.burst, i.process)
        gantt_chart.append(str)
        curr_time += i.burst
        i.exit = curr_time
    else:
        str = "[{0}-{1}] Process {2}" .format(i.arrival, i.arrival+ i.burst, i.process)
        gantt_chart.append(str)
        curr_time += (i.burst + i.arrival) - curr_time
        i.exit = i.arrival + i.burst

print( "Process ID  |" + " Waiting time  |" + " Turnaround Time")
process.sort(key = lambda x: (x.process, ))
n = 0
totalwait = 0
totaltat = 0
for i in process:
    n += 1
    i.turnAT = i.exit - i.arrival ## Calculating the turnaround time, wait time and what what's the total turnaround and wait
    totaltat += i.turnAT
    i.waitT = i.turnAT - i.burst
    totalwait += i.waitT
    
    print ("    ",i.process,"\t    |    ", i.waitT,"\t    |    ", i.turnAT,"\n" )
## Calculating the average time and throughput and printing
print("Average Waiting Time: ", totalwait/n,"\n" )
print("Average Turnaround Time: ", totaltat / n ,"\n" )
print("Throughput: ", n/curr_time,"\n" ) 

#Printing the Gantt Chart
for i in gantt_chart:
    print(i)


print("--------------------PS----------------------\n")
curr_time = 0
process = []
with open(sys.argv[1], 'r') as csvfile:
    reader = csv.reader(csvfile, skipinitialspace=True)
    linecount = 0
    for row in reader:
        if linecount == 0:
            linecount += 1
        else:
            process.append(P(row[0], row[1],row[2],row[3]))

gantt_chart = []
process.sort(key = lambda x: (x.arrival, x.priority)) ## sorting first with arrival time and then with the priority 
str = ""
for i in process:
    if (curr_time < i.arrival):
        str = "[{0}-{1}] Process {2}" .format(curr_time, i.arrival, 'IDLE')
        gantt_chart.append(str)
    if (curr_time > i.arrival):
        str = "[{0}-{1}] Process {2}" .format(curr_time, curr_time+ i.burst, i.process)
        gantt_chart.append(str)
        curr_time += i.burst
        i.exit = curr_time
    else:
        str = "[{0}-{1}] Process {2}" .format(i.arrival, i.arrival+ i.burst, i.process)
        gantt_chart.append(str)
        curr_time += (i.burst + i.arrival) - curr_time
        i.exit = i.arrival + i.burst
print( "Process ID  |" + " Waiting time  |" + " Turnaround Time")
process.sort(key = lambda x: (x.process))
nps = 0
totalwait = 0
totaltat = 0
for i in process:
    nps+= 1
    i.turnAT = i.exit - i.arrival
    totaltat += i.turnAT
    i.waitT = i.turnAT - i.burst
    totalwait += i.waitT    
    print ("    ",i.process,"\t    |    ", i.waitT,"\t    |    ", i.turnAT,"\n" )
    
print("Average Waiting Time: ", totalwait/nps,"\n" )
print("Average Turnaround Time: ", totaltat / nps ,"\n" )
print("Throughput: ", nps/curr_time,"\n" ) 

for i in gantt_chart:
    print(i)



print("--------------------Round Robin----------------------\n")
quantum = sys.argv[2]
curr_timeRR = 0
processRR = []
readyQ = []
finishedQ = []
gantt_chartRR = []
burst_time =  []
switch = True
PrevProcess = None
with open(sys.argv[1], 'r') as csvfile:
    reader = csv.reader(csvfile, skipinitialspace=True)
    linecount = 0
    for row in reader:
        if linecount == 0:
            linecount += 1
        else:
            process.append(P(row[0], row[1],row[2],row[3]))
process.sort(key = lambda x: (x.arrival, x.process))
print("RR Ready Queue:\n" )
n = 0
while True:
    for i in process:
        if i.arrival <=  curr_timeRR and i not in readyQ and i not in finishedQ:
            readyQ.append(i)
            burst_time[i.process -1] = i.burst
        elif i.arrival >=  curr_timeRR and i not in readyQ and i not in finishedQ and switch:
            print (readyQ,"\n")
            switch = False
    if len(readyQ) == 0:
        for i in process:
            if i not in finishedQ:
                 str = "[{0}-{1}] Process {2}" .format(curr_time, i.arrival, 'IDLE')
                 gantt_chartRR.append(str)
                 curr_timeRR = i.arrival
                 burst_time[i.process -1] = i.burst
                 print(readyQ,"\n")
                 break
    for r in range (len(readyQ)):
        currID = readyQ[0].process
        
        
        
        
        
                 
                
        
    

