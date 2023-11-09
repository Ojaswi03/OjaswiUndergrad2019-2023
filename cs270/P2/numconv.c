/**
 *  @author Ojaswi Sinha
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
	char ans = '0';
	if (value >= 0 &&  radix > value){
		if (value <= 9){
			ans = value + 48; 
			return ans;
		}
		else{
			ans = value + 55;
			return ans;
		}
	}
	   
	return '?';
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
	int ans = -1;
	if (digit >= '0' && digit <= '9'){
		ans = digit - 48;
	}
	else if (digit >= 'a' && digit <= 'z'){
		ans = digit - 32;
		ans -= 55;
	}
	else if ( digit >='A' && digit <= 'Z'){
		ans = digit - 55;	
	}
	if (ans < radix && ans >= 0){
		return ans;
	}	
	return -1;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
	*quotient = numerator / divisor;
	*remainder = numerator % divisor; 

}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
	int iVal;
	char val = getchar();
	if ( val == '\n'){
		return valueOfPrefix;
	}else{
		iVal = char_to_int(val, radix);
		valueOfPrefix  = valueOfPrefix * radix + iVal; 
		return ascii_to_int(valueOfPrefix , radix);
	}
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
	int rem;
	int quo; 
	div_rem( value, radix, &rem, &quo);
	if (quo > 0){
		int_to_ascii(quo, radix);
	}
	putchar(int_to_char(rem, radix));	
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  return -1.0;
}

