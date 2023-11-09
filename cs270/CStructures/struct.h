/* CS270 
 *
 * Author: Ojaswi SinhaYour name here
 * Date:   4/20/2022
 */
 
/********** STRUCTURE DEFINITION **********************************************/

// Structure that represents a student
typedef struct
{
  // TODO: Add required members
  char firstName[80];
  float qualityPoints;
  int numCredits;
} Student;

// Structure that represents a class roster
// TODO: Declare this structure
typedef struct{
  int numStudents;
  Student** students;   
} ClassRoster;
/********** FUNCTION PROTOTYPES ***********************************************/

void readStudentAndEnroll(Student **slot);

void displayStudent(Student s);
