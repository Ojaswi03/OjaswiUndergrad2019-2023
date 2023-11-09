#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Error! Need to have 2 arguements\n");
        return -1;
    }// makes sure that there are 2 arguements

    pid_t pid;
    FILE *file = fopen(argv[1],"r");
    char buff[256];
    int spStatus;
    int seStatus;
    
    while (fgets(buff ,sizeof(buff), file)){
        int parentID = getpid();
        pid = fork();
        
        if (pid < 0){
            printf( "Fork Failed\n");
            return -1;
        }
        else if (pid == 0){
            execlp("./SpecialNumbers","SpecialNumbers",buff, NULL); // starting a child process in SpecialNumbers.c
        }
        else{
            printf("[Initiator][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
            waitpid(pid, &spStatus, 0);
            printf("[Initiator][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(spStatus));       
        }
        pid = fork();
        if (pid < 0){
            printf( "Fork Failed\n");
            return -1;
        }
        else if (pid == 0){
            execlp("./SequenceNumbers","SequenceNumbers",buff, NULL);// Starting the child process in SequenceNumbers.c
        }
        else{
            printf("[Initiator][%d]: Waiting for the child process %d\n",(int)getpid(), pid);
            waitpid(pid, &seStatus, 0);
            printf("[Initiator][%d]:The child process %d returned %d\n", getpid(), pid, WEXITSTATUS(seStatus));
        }
        printf("[Initiator][%d]: The SpecialNumbers child process returned %d\n", getpid(), WEXITSTATUS(spStatus));
        printf("[Initiator][%d]: The SequenceNumbers child process returned %d\n", getpid(), WEXITSTATUS(seStatus));
        // Printing the ChildID onto the parentID 
    }
    fclose(file);
    return 0;
}

