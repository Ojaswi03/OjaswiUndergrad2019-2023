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
    
    int n = atoi(argv[0]); 
    printf("%d Padovan check\n", n);
    int p1 = 0;
    int p2 = 0;
    int p3 = 1;
    int p4 = 1;
    int sum = 0;
    char str[8];
    printf("[Padovan][%d] : The first %d numbers of the Padovan sequence are :\n", getpid(), n);
    for (int i = 0; i <=n; i++){
        p4 = p1 + p2;
        p1 = p2; // The for loop is the padovan sequence.
        p2 = p3;
        p3 = p4;
        sum += p4;
        
        printf("%d ", p4);
    }
    sprintf(str, "%d", sum);
    printf("\n[Padovan][%d]: The sum of the first %d numbers of the Padovan sequence is %d\n", getpid(), n, sum);

    int Padovan = shm_open(argv[1], O_RDWR | O_CREAT,S_IRWXU);
    void *padovan_mm = mmap(0,32,PROT_READ, MAP_SHARED, Padovan, 0);
    char res[10];
    sprintf(res,"%d", sum);
    sprintf(padovan_mm, "%s", str);
    shm_unlink(argv[1]);
    return 0;

}
