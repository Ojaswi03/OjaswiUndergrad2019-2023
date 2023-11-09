#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Ojaswi Sinha</b>
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  
  if (x >> 15 & 1){    
      return 1;  
  }    
  return 0; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
  iFloat_t xtemp = x >> 7;
  iFloat_t mask  = 255;
      
  return xtemp & mask; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
  iFloat_t mask  = 127;
  iFloat_t mask2 = 128;
  iFloat_t xtep = x & mask;
  xtep = xtep | mask2;
  if ( floatGetSign(x) == 1){
       xtep = ~xtep + 1;
       return xtep;
  }           
  return xtep;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
    *sign = floatGetSign(x);
    *exp = floatGetExp(x);
    *val = floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
  if (bits == 0){
      return -1;
  }
  iFloat_t pos = 15;
  iFloat_t mask = 0b1000000000000000;
  iFloat_t ret = 0; 
  while (pos > -1){
      ret = bits & mask;
      if (ret){
          return pos;
      }
      else{
          pos -= 1;
          mask  = 1 << pos;
      }
  }       
  return pos;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  if (floatGetSign(x) == 0){
      return x;
  }
  iFloat_t ret = 0;
  ret = floatGetVal(x);
  ret = ~(ret -1);
  ret = ret & 127;
  iFloat_t exp = floatGetExp(x);
  exp = exp << 7;
  iFloat_t mask = 0b0111111111111111;
  ret += exp;
  ret = ret & mask;
  return ret;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
  if (x == 0){
      return 0;
  }
  if (floatGetSign(x) == 1){
      return floatAbs(x);
  }
  iFloat_t mask  = 0b1000000000000000;
  return x | mask ;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  debug("%s: bits of x (bfloat16)", getBinary(x)); // example only
  debug("%s: bits of y (bfloat16)", getBinary(y)); // example only
  if ((x == 0) & (y == 0)){
      return 0;
  }
  if (x == floatNegate(y)){
      return 0;
  }
//step 1
  iFloat_t xexp, yexp, xval, yval;
  iFloat_t expShift = 0;
  iFloat_t expR = 0;
  xexp = floatGetExp(x);
  yexp = floatGetExp(y);
  xval = floatGetVal(x);
  yval = floatGetVal(y);
  

//step 2 
  if (xexp > yexp){
      expShift = xexp - yexp;
      yexp+= expShift;
      yval = yval >> expShift;
  }
  debug("%s: yval ", getBinary(yval));
  if (yexp > xexp ){
      expShift = yexp - xexp;
      xexp += expShift;
      xval = xval >> expShift;
  }
  debug("%s:xval ", getBinary(xval));
  
// step 3
  iFloat_t rmag = xval + yval;
  expR = yexp;
  
// step 4
  iFloat_t rsign = 0;
  if (floatGetSign(rmag)){
      rsign = 1;
      rmag = ~rmag + 1;
  }
  debug("%s: step 4 rmag", getBinary(rmag));
// step 5
  if (floatLeftMost1(rmag) > BITS_MANT){
     iFloat_t diff = floatLeftMost1(rmag) - BITS_MANT;
     rmag = rmag >> diff;
     expR += diff;
  }
  if (floatLeftMost1(rmag) < BITS_MANT){
     iFloat_t diff = BITS_MANT - floatLeftMost1(rmag);
     rmag = rmag << diff;
     expR -= diff;
  }
  
// step 6
  iFloat_t ret;
  iFloat_t clearmask = 0x007F;
  rmag = rmag & clearmask;
  rsign = rsign << 15;
  expR = expR << BITS_MANT ;
  debug("%s: line 164 rmag", getBinary(rmag));
  debug("%s: line 165 rsign", getBinary(rsign));
  debug("%s: line 166 expR", getBinary(expR));
  ret  = rsign + expR + rmag;
 
  return ret;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
  if ((x-y) == 0){
      return 0;
  }
  return floatAdd(x , floatNegate(y));
}

