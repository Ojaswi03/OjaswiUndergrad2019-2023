#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    printf("%d Square check\n", n);

    int sum = 0;
    char str[8];
    printf("[Square][%d] :The first %d numbers of the Square sequence are :\n", getpid(), n);
    for (int i = 1; i <= n; i++){
        sum += i*i; // using for loop to iterate to n and sum the square of number upto n.
      
        printf("%d ", i*i);
    }
    sprintf(str, "%d", sum);
    printf("\n[Square][%d]: The sum of the first %d Square sequence is %d\n",getpid(), n, sum);
    
    int Square = shm_open(argv[1], O_RDWR | O_CREAT,S_IRWXU);
    void *square_mm = mmap(0,32,PROT_READ, MAP_SHARED, Square, 0);

    char res[10];
    sprintf(res,"%d", sum);
    sprintf(res,"%d", sum);
    sprintf(square_mm, "%s", str);
    shm_unlink(argv[1]);
    return 0;

}
