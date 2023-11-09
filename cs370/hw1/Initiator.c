#include <stdio.h>
#include <stdlib.h>
#include "Worker.h"

int main(int argc, char *argv[]) {
  if (argc != 2){
    printf("Only 2 parameters allowed [./Initiator] and seed \n");
    return -1;
  }
  int t = atoi(argv[1]);
  srand(t);
  printf("[Initiator]: With seed: %d\n", t);
  float running_ratio = get_running_ratio();
  printf("[Initiator]: Running ratio: %f\n", running_ratio);
  return 0;

}

