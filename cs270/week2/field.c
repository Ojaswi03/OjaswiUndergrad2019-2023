#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Ojaswi Sinha</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	int  mask = 1;
	unsigned int result;
    
	mask = mask << position; 
	result = value & mask;
	result = result >> position; 
	return result;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	int mask = 1;
	
	mask = mask << position;
	value= value | mask;
	
	return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
	int mask = 1;
	
	mask = mask << position;
	value = value & ~mask; 	
	return value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	int mask = 1;
	int field,flip;
	int num = hi-lo + 1;
	mask = mask << num;
	mask = mask - 1;
	mask = mask << lo;
	field = value & mask;
	if (isSigned &&  getBit(field, num - 1) == 1){
		flip  = ~field + 1;
		return flip;			
	}
	return field;

}
