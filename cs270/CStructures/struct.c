/* CS270 
 *
 * Author: Ojaswi Sinha
 * Date:   4/20/2022
 */

#include "struct.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
 /* *slot = malloc(sizeof(student));
  scanf("%s", (*slot).firstName);
  scanf("%d", (*slot).qualityPoints); 
  */
  Student* s = (Student*) malloc(sizeof(Student));
  scanf("%s", s->firstName);
  scanf("%f", &(s->qualityPoints));
  scanf("%d", &(s->numCredits));
  *slot = s;
}

void displayStudent(Student s)
{
  // 2 line 
  // name and claculate gpa and display
  float gpa = s.qualityPoints / s.numCredits;
  printf ("%s, %.2f\n",s.firstName, gpa);

}
