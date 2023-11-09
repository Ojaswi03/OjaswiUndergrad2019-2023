1. What value does fork() return in a child process?
Answer: Upon successful com[pletion, fork() returns 0 to the child process and retruns the process ID of the child
        process to the parent process.

2. What can cause fork() to fail?
Answer: When there are too many porcessess on the system then the fork() fails.

3. How many of the least significant bits of the status does WEXITSTATUS return?
Answer: WEXITSTATUS(wstatus) returns the exit status of the child. This consists of the least significant 8 bits of 
        the status argument that the child specified in a call to exit(3) or _exit(2) or as the argument for a return
         statement in main()

4. Which header file must be included to use the WEXITSTATUS.
Answer: The header file should be <sys/wait.h>.

5. In this program, are we doing a sequential processing or a concurrent processing with respect to the child 
   processes? (Sequential processing is   when only one of the child processes is running at one time, and concurrent
   processing is when more than one child process ca be running at the same time.)
Answer: In this program we arw doing sequential processing by going to one child process to another and if the child
        dies we then move to the next sequence.

6. Is it possible to have any anomalies in the output from a child process and the output from the parent process. 
   When can that happen? (2 pints)
Answer: We have anomalies when the child process becomes a zombie because its not killed.
