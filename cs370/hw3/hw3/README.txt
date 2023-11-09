1. What are the differences between pipe and shared memory? Give at least two differences (2 points)
Answer: Pipes: Can switch between blocking and non-blocking mode. Don't have to free them when done.
        Shared memory: Can store structures. Won't ever block - positive

2. Which ends of the pipe denote the read and the write ends of a pipe? (1 point)
Answer: pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe.

3. Why closing a file descriptor is required when reading or writing to a pipe? (1 point)
Answer: if you do not close the descriptors the system will keep extra entries in the open file table.

4. Why the output of the program Initiator isn’t always same? (1 point)
Answer: Since the pipes are unidirectional the output isn't always the same.