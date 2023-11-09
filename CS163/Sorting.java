// Sorting.java - initial code for sorting lab
// Author: ?????
// Date:   ?????
// Class:  CS163/CS164
// Email:  ?????

import java.util.Arrays;

public class Sorting {

    // Size of array
    private static final int MAXSIZE = 50000;

    // Main entry point
    public static void main(String args[]) {

        // Initialize data in different ways
        for (int option = 0; option < 4; option++) {

            switch (option) {
            case 0:
                System.out.println("COMPLETELY RANDOM:");
                break;
            case 1:
                System.out.println("HALF SORTED:");
                break;
            case 2:
                System.out.println("REVERSE ORDER:");
                break;
            case 3:
                System.out.println("ALREADY SORTED:");
            }

            // Verify and measure different kinds of sorting
            for (int sort = 0; sort < 4; sort++) {
                measureSorting(option, sort);
            }
            System.out.println();
        }
    }

    private static void measureSorting(int option, int sort) {

        long starttime = 0; // starting clock tick
        long finaltime = 0; // ending clock tick
        FillArray array = new FillArray(MAXSIZE);
        String label = "";

        double[] unsortedArray = array.fillArray(option);
        starttime = System.nanoTime();
        switch (sort) {

        case 0: bubbleSort(unsortedArray);          // student code
        label = "Bubble";
        break; 
        case 1: selectionSort(unsortedArray);       // student code
        label = "Selection";
        break; 
        case 2: insertionSort(unsortedArray);       // provided code 
        label = "Insertion";
        break;
        case 3: Arrays.sort(unsortedArray);     // native quicksort 
        label = "Quick";
        break; 
        }
        finaltime = System.nanoTime();

        // Make sure it is sorted
        array.checkArray(unsortedArray);

        // Print timing information
        long millis = (finaltime - starttime) / 1000000; // nano to micro 
        System.out.println(label + " sort of " + MAXSIZE + " elements = " + millis + " milliseconds");
    }

    // Bubble sorting
    public static void bubbleSort(double[] values) {

        // STUDENT CODE HERE

    }

    // Selection sorting
    public static void selectionSort(double[] values) {

        // STUDENT CODE HERE

    }

    // Insertion sorting
    public static void insertionSort(double[] values) {

        int i,j;

        // Outer loop
        for (i = 1; i < values.length; i++) {

            // Current value
            double value = values[i];

            // Inner loop
            for (j = i-1; j >= 0 && value < values[j]; j--) 
            {
                values[j+1] = values[j];
            }

            // Value is sorted
            values[j+1] = value;
        }
    }
}


