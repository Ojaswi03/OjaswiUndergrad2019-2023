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

int main (int argc, char * argv[]){

    if(argc != 3){
        printf("Error! Need 3 arguemts only.");
        return -1;
    }
    char buff[256];
    FILE *file = fopen(argv[1], "r");
    int sum = 0;
    while(fgets(buff, sizeof(buff), file)){
        sum += atoi(buff);
    }
    int modded = sum % 99999999;
    int ref = atoi(argv[2]);
    char smod[sum];
    char ssum[sum];
    sprintf(smod,"%d", modded );
    sprintf(ssum,"%d", sum );
   
    if ((int) sum > 99999999){
        write(ref, smod, sum);
    }
    else{
        write(ref, ssum, sum);
    }
    close(ref);
    fclose(file);
    return 0;
}
