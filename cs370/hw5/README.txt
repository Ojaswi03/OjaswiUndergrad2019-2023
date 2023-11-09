README
======

This package includes the following files.

|-- Coordinator.java [Coordinator gets all the value and initializes everything] (Skeleton Code provided)
|-- Generator.java [The generators are responsible for producing data items to be added to the buffer.] (Skeleton Code provided)
|-- Consumer.java [The consumers are responsible for consuming elements, produced by the generator, from the buffer.]
|-- Buffer.java [keeps track of the buffer if its empty or full and inserts or remove the data fromthe array]
|-- Makefile [makes the class, cleans tar file]
|-- README.txt [This file]


Questions:

1. In which function do you override the body to define the new body of a thread in java? ____run()______. - 1 point

2. The problem of producer consumer is solved using ______b____. - 1 point
	a. Mutex Locks
	b. Semaphores

3. What conditions make deadlock in this homework? - 1 point
	An endless while waiting loop

4. What two functions defined in Java are used for synchronization between producer and consumers in your program? _____notifyall_____ and ____wait()______. - 2 points

5. Which function is used to wait for a thread to finish and come back to calling program i.e. for a thread to die? ___Join()_______. - 1 point

NOTE:

Lab systems by default use Java 11 which supports nanosecond timestamp. If after logging in and running 'java -version', it doesn't output version 11, use the following two commands:

	$ export PATH=/usr/lib/jvm/jre-11-openjdk/bin/:$PATH

	$ export LD_LIBRARY_PATH=/usr/lib/jvm/jre-11-openjdk/lib/:$LD_LIBRARY_PATH


