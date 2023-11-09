#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    int sum = 0;
    for (int i = 1; i <= n; i++){
        sum += i*i; // using for loop to iterate to n and sum the square of number upto n.
    }
    printf("[Square][%d]: The sum of the first %d squares is %d\n",getpid(), n, sum);
    if (sum < 100){
        return sum;
    }
    else{
        return 100;
    }

}
