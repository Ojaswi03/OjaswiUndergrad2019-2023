README
======

A. This package includes the following files. In your own readme file, modify the information as needed.

|-- Description PDF of the assignment
|-- README.txt [This file]


B. Use your designed makefile 
To compile the code and build the executable using the command 

systemprompt>  make

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming seed is 3) 

systemprompt> ./Initiator 3

which will run the program and generate the outputs.


C. Answer the following questions (1 point each, select/type the right answer).

  1. What is the main difference between Malloc() and Calloc()?
     Ans: malloc() function creates a single block of memory of a specific size. calloc() function assigns multiple 
          blocks of memory to a single variable.

  2. What is the advantages of using dynamic memory allocation?
     Ans: There is nor wastage of memory. Memmory allocation is done during run time. The size of the memory can be 
          changed based on the dynamic memory allocation requirements.

  3. What happens if you attempt to free the memory already freed?
     Ans: Nothing will happen, the program will crash, memory will be corrupted and many more depending the on system 
          we run the code on.

  4. What is the purpose of the headerfile Worker.h, and why is Initiator.h not necessary?
     Ans: Worker.h is a file that links Initiator.c and Worker.c. Since Initiator.c invokes Worker.c and lets Worker.c do          the main task, it makes sense to have only Worker.h.  
  5. Describe the * and & operators in the context of pointers and references?
     Ans: Pointers:These are variables that holds memory address of another variable. You dereference with a "*"                   operator to access the memory location that it points to.
          Reference: This variable is an alias for an already existing variable. It can be thought as a constant pointer.                     
