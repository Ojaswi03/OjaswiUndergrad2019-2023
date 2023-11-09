 /** @mainpage 
   *  \htmlinclude "STRUCTS.html"
   */
/* CS270 
 *
 * Author: Ojaswi Sinha
 * Date:   4/20/2022
 */
#include<stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
  // TODO: Complete the main function
  int num_students;
  scanf("%d", &num_students);
  ClassRoster roster;
  roster.numStudents = num_students;
  roster.students = (Student**)  calloc(num_students, sizeof(Student*));  
  for (int i  = 0; i < num_students; i++){
      readStudentAndEnroll(&roster.students[i]);  
  }
  for (int i = 0; i < num_students; i++){
      displayStudent(*roster.students[i]);
      free(roster.students[i]);
  }
  free(roster.students);
  return 0;
}
