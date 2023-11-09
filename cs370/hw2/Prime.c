#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ( int argc, char *argv[]){

    int  n = atoi (argv[1]);
    
    int sum = 0;
    if (n == 0 || n == 1) { // 0 and 1 are mot prime numbers
        return 0;
    }
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
    printf("[Prime][%d]: The sum of the prime numbers <= %d is %d\n",getpid(), n, sum);
    if (sum < 100){
        return sum;
    }
    else{
        return 100;
    }


} 
