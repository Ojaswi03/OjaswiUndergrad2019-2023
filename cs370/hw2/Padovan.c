#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    int n = atoi(argv[1]); 
    int p1 = 0;
    int p2 = 0;
    int p3 = 1;
    int p4 = 1;
    int sum = 0;
    for (int i = 0; i <=n; i++){
        p4 = p1 + p2;
        p1 = p2; // The for loop is the padovan sequence.
        p2 = p3;
        p3 = p4;
        sum += p4;
    }
    printf("[Padovan][%d]: The sum of the first %d numbers of the Padovan sequence is %d\n",getpid(), n, sum);
    if (sum < 100){
        return sum;
    }
    else{
        return 100;
    }
}
