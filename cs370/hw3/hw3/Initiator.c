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

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Error! Need to have 2 arguements\n");
        return -1;
    }// makes sure that there are 2 arguements

    pid_t pid;
    char buff[256];
    pid = fork();
    int fd[2];
    int pipRes = pipe(fd);
    sprintf(buff, "%d", fd[WRITE_END]);
    char ref[16];
    sprintf(ref, "%d", fd[1]);
    int stat;
    int readerStat;
    char n[10];
    int childstat;
    

    if (pipRes < 0 ){
        printf("Initiator[%d]: Pipe creation failed!\n", getpid());
        return -1;
    }
    else if (pid == 0){
        close(fd[0]);
        execlp("./Reader","Reader", argv[1], ref, NULL);
    }
    else{
        waitpid(-1, &stat, 0);
        readerStat = WEXITSTATUS(stat);
        close(fd[1]);
        read(fd[0], &n, 10);
        close(fd[0]);
        printf("[Initiator][%d] : Contents read from read end pipe :%d\n", getpid(), atoi(n));
    }
   // Creating shared memory for each child.
    // Prime
    int Prime = shm_open("SHM_Prime", O_RDWR | O_CREAT,S_IRWXU);
    ftruncate(Prime, 10);
    caddr_t *prime_mm = mmap(0,32,PROT_READ, MAP_SHARED, Prime, 0);
    printf("[Initiator][%d] : Created Shared memory \"SHM_Prime\" with FD: %d\n", getpid(),Prime );

    // Square
    int Square = shm_open("SHM_Square", O_RDWR | O_CREAT,S_IRWXU);
    ftruncate(Square, 10);
    caddr_t *square_mm = mmap(0, 32, PROT_READ, MAP_SHARED, Square, 0);
    printf("[Initiator][%d] : Created Shared memory \"SHM_Square\" with FD: %d\n", getpid(),Square );

    // Padovan
    int Padovan = shm_open("SHM_Padovan", O_RDWR | O_CREAT,S_IRWXU);
    ftruncate(Padovan, 10);
    caddr_t *padovan_mm = mmap(0,32,PROT_READ, MAP_SHARED, Padovan, 0);
    printf("[Initiator][%d] : Created Shared memory \"SHM_Padovan\" with FD: %d\n", getpid(), Padovan );

    // Perrin
    int Perrin = shm_open("SHM_Perrin", O_RDWR | O_CREAT,S_IRWXU);
    ftruncate(Perrin, 10);
    caddr_t *perrin_mm = mmap(0,32,PROT_READ, MAP_SHARED, Perrin, 0);
    printf("[Initiator][%d] : Created Shared memory \"SHM_Perrin\" with FD: %d\n", getpid(),Perrin);

    pid_t pid2;

    // Calling the child process.

    for(int i = 0; i < atoi(argv[1]); i++) {
        pid2 = fork();
        if (pid2 < 0) {
            printf("Error");
            return -1;
        } 
        else if (pid2 == 0) {
            if (i == 0){
                return execlp("./Prime","Prime", "SHM_Prime", n, NULL);
            }
            else if (i == 1) {
                return execlp("./Square","Square", "SHM_Square", n, NULL);
            }
            else if (i == 2){
                return execlp("./Padovan","Padovan", "SHM_Padovan", n, NULL);
            }
            else if (i == 3){
                return execlp("./Perrin","Perrin", "SHM_Perrin", n, NULL);
            }
        }
    }
    for (int j = 0; j < atoi(argv[1]); j++){
        waitpid(-1, &childstat, 0);
    }
       
}

