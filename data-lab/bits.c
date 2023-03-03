/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   * x ^ y = (x & ~y) | (~x & y)
   *       = ~(~(x & ~y) & ~(~x & y))
   */
  return ~(~(x & ~y) & ~(~x & y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { return 1 << 31; }
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* A && B == !!A & !!B */
  return !!!(x ^ ~(x + 1)) & !!(x + 1);
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* A == b == !(A ^ B) */
  int target = (0xAA << 24) | (0xAA << 16) | (0xAA << 8) | 0xAA;
  return !((x | target) ^ x);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return (~x) + 1; }
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  return !((x & ~0x3F) | ((x | 0x30) ^ x) |
           (!((x | 0x0A) ^ x) | !((x | 0x0C) ^ x)));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int maskTrue = (!x) + ((~1) + 1);
  return (maskTrue & y) | (~maskTrue & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int delta_yx = ~x + y + 1; // this should not be less than 0
  int res = !((delta_yx >> 31) & 1);
  int x_neg = (x >> 31) & 1;
  int y_neg = (y >> 31) & 1;
  int maskTrue_x_neg_and_y_pos = (~x_neg | y_neg) + ~0;
  int maskTrue_x_pos_and_y_neg = (~y_neg | x_neg) + ~0;
  return (~maskTrue_x_pos_and_y_neg &
          ((maskTrue_x_neg_and_y_pos & 1) | (~maskTrue_x_neg_and_y_pos & res)));
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int r1 = x | (x >> 16);
  int r2 = r1 | (r1 >> 8);
  int r3 = r2 | (r2 >> 4);
  int r4 = r3 | (r3 >> 2);
  int r5 = r4 | (r4 >> 1);
  return (r5 & 1) ^ 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int old_x = x;
  int r = 0;
  int mask_zero_or_minus_one;
  x = ((!!(old_x & (1 << 31)) + ~0) & x) | ((!(old_x & (1 << 31)) + ~0) & ~x);
  r = r + ((!(x >> 16) + ~0) & 16);
  x = x >> ((!(x >> 16) + ~0) & 16);
  r = r + ((!(x >> 8) + ~0) & 8);
  x = x >> ((!(x >> 8) + ~0) & 8);
  r = r + ((!(x >> 4) + ~0) & 4);
  x = x >> ((!(x >> 4) + ~0) & 4);
  r = r + ((!(x >> 2) + ~0) & 2);
  x = x >> ((!(x >> 2) + ~0) & 2);
  r = r + ((!(x >> 1) + ~0) & 1);
  x = x >> ((!(x >> 1) + ~0) & 1);
  r = r + 2;
  mask_zero_or_minus_one = !(!(old_x) | !(~old_x)) + ~0;
  return (mask_zero_or_minus_one & 1) | (~mask_zero_or_minus_one & r);
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned exp_mask = (0xFF << 23);
  unsigned sign = uf & (1 << 31);
  unsigned exp = uf & exp_mask;
  unsigned f = uf ^ sign ^ exp;
  if (!(~exp & exp_mask)) {
    return uf; // nan or inf
  };
  if (!exp && !f) {
    return uf; // zero
  }
  if (!exp) {
    // denormalized
    return sign | exp | (f << 1);
  }
  return sign | (exp + (1 << 23)) | f;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned sign = (uf >> 31) & 1;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned f = uf ^ (sign << 31) ^ (exp << 23);
  int ans = 1;
  unsigned valid = 0;
  if (!~exp) {
    return (1 << 31); // nan or inf
  };
  if (!exp && !f) {
    return 0; // zero
  }
  if (exp < 127) {
    // is very small, so return 0
    return 0;
  }
  while (exp > 127) {
    if (valid < 23) {
      exp -= 1;
      ans = (ans << 1) + (f & (1 << (22 - valid)));
      valid += 1;
    } else {
      exp -= 1;
      if (ans & (1 << 30)) {
        return 1 << 31;
      }
      ans <<= 1;
    }
  }
  if (sign) {
    return -ans;
  } else {
    return ans;
  }
  //
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  unsigned ux = x;
  int f = 149 - x;
  if ((x >> 7) && !(x >> 31)) {
    return 0xFF << 23;
  }
  if ((ux >> 31) && ((-x) >> 7)) {
    // denormalized or zero
    if (f <= 0) {
      return 0;
    } else {
      return 1 << f;
    }
  }
  return (127 + x) << 23;
}
