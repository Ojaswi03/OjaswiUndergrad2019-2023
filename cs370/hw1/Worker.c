#include <stdio.h>
#include <stdlib.h>
#include "Worker.h" // Links worker.h file and allows Initiator.c to access Worker.c

float get_running_ratio(){
  
  int maxCountIteration, maxCountVowel = 0;
  float sratio = 0.0;
  int it = random_in_range(50,100); // Assigning random number of iteration that's gonna take place

  for (int k = 1; k <= it; k++){
    int size = random_in_range(150,200);
    char* arr = (char*) malloc(size * sizeof(char)); // Dynamically allocate memory
    for (int i = 0; i < size ; i++){
      arr[i] = random_in_range('A', 'Z'+1);
    }

    int count = get_vowel_count(arr, size);

    if (maxCountVowel < count ){
        maxCountVowel = count;  // takes the max number  of vowels and stores it in maxCountVowel
        maxCountIteration = k; 
    }

    float ratio = (float) count / (size - count);
    sratio += ratio;  // Sum of all the ratios later needs to be averaged out
    free(arr);
  }
  
  float avgRatio = (float) sratio / it;
  printf("[Worker]: Number of iterations is: %d\n", it);
  printf("[Worker]: Iteration with maximum vowel count is: %d\n", maxCountIteration);
  return avgRatio;

}

int get_vowel_count( char *array, int arraySize){
  int count = 0;
  for (int j = 0; j < arraySize; j++){
    if (array[j] == 'A' || array[j] == 'E'|| array[j] =='I'||array[j] == 'O'|| array[j] == 'U'){
      count += 1;
    }
  }
  return count;
}

int random_in_range( int lower_bound, int upper_bound){
  return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}
