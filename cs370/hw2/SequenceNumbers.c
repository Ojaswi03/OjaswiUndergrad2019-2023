#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
    int padstatus;
    int perstatus;
    int pid = fork();
    int parentID = getpid();
    if (pid < 0){
        printf( "Fork Failed\n");
        return -1;
    }
    else if (pid == 0){
        execlp("./Padovan","Padovan", argv[1], NULL); //  Starting ther child process Padovan.c
    }
    else{
        printf("[SequenceNumbers][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
        waitpid(pid, &padstatus, 0);// Waiting for Padovan.c to terminate
        printf("[SequenceNumbers][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(padstatus));
    }
    pid = fork();
    if (pid < 0){
        printf( "Fork Failed\n");
        return -1;
    }
    else if (pid == 0){
        execlp("./Perrin","Perrin",argv[1], NULL); // Starting the child process Perrin.c
    }
    else{
        printf("[SequenceNumbers][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
        waitpid(pid, &perstatus, 0);// Waiting for perrin.c to terminate.
        printf("[SequenceNumbers][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(perstatus));
    }
    printf("[SequenceNumbers][%d]: The padovan child process returned %d\n", parentID, WEXITSTATUS(padstatus));
    printf("[SequenceNumbers][%d]: The perrin child process returned %d\n", parentID, WEXITSTATUS(perstatus));
    return 0;

}
