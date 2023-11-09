Q1) Is the Shortest Remaining Time First a non-preemptive Algorithm?
Answer: Shortest Remaining Time First (SRTF) is the preemptive version of Shortest Job Next (SJN) algorithm,
        where the processor is allocated to the job closest to completion.

Q2) What are the 5 different states a process can be in scheduling (Look into process state
diagram)?
Answer: New(process is being created), Ready( The process is waiting to be assigned to a processor), 
        Running(Instructions are being executed), Wait(The process is waiting for some event to occur (such as an 
        I/O completion or reception of a signal)), and Terminate(The process has finished execution.).


Q3) Shortest Job First is like Priority Scheduling with the priority based on ______ of the process?
Answer: Shortest burst time

Q4) ________ effect is the primary disadvantage of First Come First Serve Scheduling algorithm.
Answer: Convoy

Q5) How does Multi Level Feedback queue prevent starvation of processes that waits too long in lower priority queue?
Answer: The idea is to separate processes with different CPU-burst characteristics. If a process uses too 
        much CPU  time, it will be moved to a lower-priority queue. Similarly, a process that waits too long in a lower-priority queue may be moved to a higher-priority queue. This form of aging prevents starvation
