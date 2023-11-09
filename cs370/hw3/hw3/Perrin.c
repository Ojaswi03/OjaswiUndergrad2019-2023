#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main( int argc, char *argv[]){

    int n = atoi(argv[1]);
    int p0 = 3;
    int p1 = 0;
    int p2 = 2;
    int p3 = 0;
    int sum = 5;
    if (n == 0){
        sum = 0;    
    }
    else if (n == 1){
        sum = 3;
    }
    else if (n == 2){
        sum = 3;
    }
    char str[8];
    printf("[Perrin][%d] :The first %d numbers of the Perrin sequence are :\n", getpid(), n);
    for (int i = 3 ; i < n; i++){
        p3 = p1 + p0;
        p0 = p1;// Add the first 2 numbers and the swap the place of the first number with second and second with
        p1 = p2;// third and so on and after each iteration store and keep on adding on to the sum
        p2 = p3;
        sum += p3; 
        printf("%d ", p3);
    }
    sprintf(str, "%d", sum);
    printf("\n[Perrin][%d]: The sum of the first %d numbers of the Perrin sequence is %d\n",getpid(), n, sum);

    int Perrin = shm_open(argv[1], O_RDWR | O_CREAT,S_IRWXU);
    void *perrin_mm = mmap(0,32,PROT_READ, MAP_SHARED, Perrin, 0);
    char res[10];
    sprintf(res,"%d", sum);
    sprintf(perrin_mm, "%s", str);
    shm_unlink(argv[1]);
    return 0;

}
