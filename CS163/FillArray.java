// FillArray.java - utility code to fill array with random values
// Author: Chris Wilcox, original by Russ Wakefield
// Date:   11/20/2016
// Class:  CS163/CS164
// Email:  wilcox@cs.colostate.edu

import java.util.Random;

public class FillArray {

	// Class variables
    private static double[] randomArray;
    private static int randomSize = 0;
    private static Random randomObject;

    // Constructor
    public FillArray(int size) {

    	randomSize = size;
    	randomArray = new double[size];
    	randomObject = new Random();
    	randomObject.setSeed(12345678); // guarantee repeatability
        for (int i = 0; i < size; i++) { 
        	randomArray[i] = randomObject.nextDouble() * size;
        }
    }

    // Fill an array with variants of random numbers
    public double[] fillArray(int option) throws IllegalArgumentException {

        double[] values = new double[randomSize];
        switch (option) {

        case 0: // Completely random
            for (int i = 0; i < randomSize; i++)
                values[i] = randomArray[i];
            break;
            
        case 1: // Half sorted
            int half = randomSize / 2;
            for (int i = 0; i < half; i++)
                values[i] = randomArray[i];
            for (int i = half + 1; i < randomSize; i++)
                values[i] = (double)i;
            break;
            
        case 2: // Reverse order
            for (int i = 0; i < randomSize; i++)
                values[randomSize - i - 1] = (double)i;
            break;

        case 3: // Already sorted
            for (int i = 0; i< randomSize; i++)
                values[i] = (double)i;
            break;

        default:
            throw new IllegalArgumentException();
        }
        return values;
    }

    // Check an array to make sure it is sorted
    public boolean checkArray(double[] array) {
    	
    	// Useful for debugging
    	// System.out.println(Arrays.toString(array));
    	
    	// Check array reference
        if (array == null) {
            System.out.println("Null array passed to checkArray!");
            return false;
        }
        
        // Check array size
        else if (array.length != randomSize) {
            System.out.println("Incorrect size array passed to checkArray!");
            return false;
        }
        
        // Check array contents
        else {
        	// System.out.println("ARRAY: " + Arrays.toString(array));
        	for (int i = 0; i < array.length - 1; i++)
        		if (array[i] > array[i + 1]) {
                System.out.println("Array not sorted correctly, " + array[i]
                        + " at " + i + " is greater than " + array[i + 1]
                        + " at " + (i + 1));
                return false;
           }
        }
        return true;
    }
}
