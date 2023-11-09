# Makefile for Towers of Hanoi (LC3 assembly with provided C implelemenntation)

HEADERS    = $(wildcard *.h)
SRCS       = $(wildcard *.c)
OBJS       = $(SRCS:.c=.o)

GCC        = gcc
GCC_FLAGS  = -g -std=c11 -Wall
DEFINES    = -DDEBUG

EXE        = hanoi

LC3ASM     = $(wildcard *.asm)
LC3OBJ     = $(LC3ASM:.asm=.obj)
LC3SYM     = $(LC3ASM:.asm=.sym)

.PHONY :  all clean

# Pattern rule to compile .c file to .o file
%.o : %.c ; $(GCC) -c $(GCC_FLAGS) $(DEFINES) $<

# Pattern rule to assemble .asm file to .obj/.sym files
%.obj : %.asm ; ~cs270/lc3tools/lc3as $<

all: $(LC3OBJ) $(EXE)

$(EXE) : $(OBJS)
	$(GCC) $(GCC_FLAGS) -o $(EXE) $(OBJS) $(LIB)

clean :
	rm -f $(OBJS) $(EXE) $(LC3OBJ) $(LC3SYM)

