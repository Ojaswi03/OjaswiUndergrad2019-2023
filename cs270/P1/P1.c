// P1 Assignment
// Author: Ojaswi Sinha
// Date: 1/22/2022
// Class: CS270
// Email: ojaswi@colostate.edu

// Includes files

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double input[5];
double output[4];

void computeSphere(double radius, double *volumeAddress){
	double result = (4.0/3.0)*3.141593*radius*radius*radius;
	*volumeAddress = result;

}

void computeCube(double side, double *volumeAddress){
	double result = side * side * side;
	*volumeAddress = result;

}

void computeTetrahedron (double side, double *volumeAddress){
	double result = 0.117851 * side * side * side;
	*volumeAddress = result;
}

void computeCylinder (double radius, double height, double *volumeAddress){
	double result = 3.141593 * radius * radius * height;
	*volumeAddress = result;
}



int main (int argc, char *argv[]){

	//check # of arguements
	if (argc != 6){
		printf ("usage: ./P1 <double> <double> <double> <double> <double>\n");
		return EXIT_FAILURE;
	}

	input[0] = atof(argv[1]);
	input[1] = atof(argv[2]);
	input[2] = atof(argv[3]);
	input[3] = atof(argv[4]);
	input[4] = atof(argv[5]);
	
	
	computeSphere(input[0], &output[0]);
	computeCube(input[1], &output[1]);
	computeTetrahedron(input[2], &output[2]);
	computeCylinder(input[3],input[4], &output[3]);
	
	printf("SPHERE, radius = %.5f,", input[0]);
	printf(" volume = %0.5f.\n", output[0]);

	printf("CUBE, side = %.5f", input[1]);
	printf(", volume = %.5f.\n", output[1]);

	printf("TETRAHEDRON, side = %.5f", input[2]);
	printf(", volume = %0.5f.\n", output[2]);

	printf("CYLINDER, radius = %.5f", input[3]);
	printf(", height = %.5f", input[4]);
	printf(", volume = %.5f.\n", output[3]);
	
	return EXIT_SUCCESS;
	
}
