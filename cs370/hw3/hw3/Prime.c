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

int main ( int argc, char *argv[]){

    int  n = atoi (argv[1]);
    
    int sum = 0;
    char str[8];
    if (n == 0 || n == 1) { // 0 and 1 are mot prime numbers
        return 0;
    } 
    printf("[Prime][%d] :The first %d numbers of the Prime sequence are :\n", getpid(), n);
    for (int i = 2; i <= n; i++){
        int  prime = 1;// boolean condition to make sure we add only the prime numbers
        for (int j = 2; j < i; j++){
            if (i%j == 0){
                prime= 0;
                break; 
            }            
        }
        
        if (prime){
            sum += i;// Prime numbers being added after satisfying the condition
        }
    }
    sprintf(str, "%d", sum);
    printf("\n[Prime][%d]: The sum of the first %d numbers of the Prime sequence is :\n",getpid(), n, sum);

    int Prime = shm_open(argv[1], O_RDWR | O_CREAT,S_IRWXU);
    void *prime_mm = mmap(0, 32, PROT_READ, MAP_SHARED, Prime, 0);

    char res[10];
    sprintf(res,"%d", sum);
    sprintf(prime_mm, "%s", str);
    shm_unlink(argv[1]);
    return 0;

} 
