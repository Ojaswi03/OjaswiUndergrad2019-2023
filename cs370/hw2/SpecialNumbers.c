#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){

    
    int primestatus;
    int squarestatus;
    int pid = fork();
    int parentID = getpid();
    if (pid < 0){
        printf( "Fork Failed\n");
            return -1;
        }
        else if (pid == 0){
            execlp("./Prime","Prime", argv[1], NULL);// Starting the child process Prime.c
        }
        else{
            printf("[SpecialNumbers][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
            waitpid(pid, &primestatus, 0);// Waiting for the child to complete its task and get terminated
            printf("[SpecialNumbers][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(primestatus));
        }
        pid = fork();
        if (pid < 0){
            printf( "Fork Failed\n");
            return -1;
        }
        else if (pid == 0){
            execlp("./Square","Square",argv[1], NULL);// Starting for the child process Square.c
        }
        else{
            printf("[SpecialNumbers][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
            waitpid(pid, &squarestatus, 0);// Waiting for Square.c to terminate.
            printf("[SpecialNumbers][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(squarestatus));
        }
        printf("[SpecialNumbers][%d]: The prime child process returned %d\n", parentID, WEXITSTATUS(primestatus));
        printf("[SpecialNumbers][%d]: The square child process returned %d\n", parentID, WEXITSTATUS(squarestatus));
        return 0;        
}
