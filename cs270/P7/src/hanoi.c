/** @file hanoi.c
 *  @brief  A `C` implementation that you may use as a guide for your LC3 code
 *  @author Fritz Sieker
 */

#include <stdlib.h>
#include <stdio.h>

#include "Debug.h"

/** keep track of stack frames (excluding main) */
static int sfNum = 0;

/** used to print a tower number */
char digits[] = "0123456789";

/** Print the move of a disk from one tower to another
 *  @param disk - number of disk
 *  @param from number of original tower
 *  @param to tower to move disks to
 */
void printMove (int disk, int from, int to) {
  debug("enter sfNum: %d", ++sfNum);
  printf("Move disk %c from tower %c to tower %c\n",
         digits[disk], digits[from], digits[to]);
  debug("leave sfNum: %d", sfNum--);
}

/** Recursive implementation of Towers of Hanoi
 *  @param numDisks number of disks on from tower
 *  @param fromTower number of original tower
 *  @param toTower tower to move disks to
 */
void hanoi (int numDisks, int fromTower, int toTower) {
  int auxTower;

  debug("enter hanoi(%d, %d, %d) sfNum: %d", numDisks, fromTower, toTower, ++sfNum);

  if (numDisks == 1) {
    printMove(numDisks, fromTower, toTower);
  }

  else {
    auxTower = 6 - (fromTower + toTower);
    hanoi(numDisks - 1, fromTower, auxTower);
    printMove(numDisks, fromTower, toTower);
    hanoi(numDisks - 1, auxTower, toTower);
  }
  debug("leave hanoi(%d, %d, %d) sfNum: %d", numDisks, fromTower, toTower, sfNum--);
}

/** Entry point of program
 *  You can optionally pass the number of disks, the
 *  from tower, and the to tower as command line arguments.
 *  If not set, they default to 4, 1, and 3.
 *  Run it with the `-debug` flag to trace the program flow
 *  @param argc number of arguments
 *  @param argv array of parameters
 *  @return retuns 0, the linux convention for success
 */
int main (int argc, const char* argv[]) {
  int num  = 4;
  int from = 1;
  int to   = 3;
  
  debugInit(&argc, argv);

  if (argc == 4) {
    num  = atoi(argv[1]);
    from = atoi(argv[2]);
    to   = atoi(argv[3]);
  }
  else if (argc != 1) {
    printf("usage: hanoi [-debug] [numDisks fromDisk toDisk]\n");
    exit(1);
  }

  hanoi(num, from, to);

  return 0;
}
