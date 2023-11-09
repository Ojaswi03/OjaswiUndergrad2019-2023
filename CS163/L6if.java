/*
 * This file was created for cs163/4 Interfaces lab by Jared Crouse 8-21-2019
 */
public interface L6if {
	double LB_KG_CONST = 0.45359237;
	
	double toPounds(double kilograms);
	
	double toFahrenheit(double celsius);
	
	int toASCII(char letter);
	
	String webify(String normal);
	
	boolean isEven(int num);
}
