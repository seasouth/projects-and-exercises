/**
 * @file md5.h
 * @author Cole Southern, David Sturgill
 *
 * Header file for the md5.c file, which stores he md5 struct which contains
 * the four field states which will be modified. This file contains the bulk
 * of the algorithm involving hashing the contents of the given input file.
 * Also, this file contains the shift and noise arrays which are included in
 * the algorithm at each iteration.
 */

#ifndef _MD5_H_
#define _MD5_H_

#include "buffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Number of bytes in a block used int he MD5 calculation. */
#define MD5_BLOCK 64
/**
 * Number of bits in 2 bytes, also number of unsigned integers
 * in the array used by the md5Iteration function.
 */
#define WORD 16
/** Number of bits in 1 byte. Helps with byte reversal. */
#define BYTE 8
/** Half the number of bits in a byte. Helps with byte reversal. */
#define HALF_BYTE 4
/** Predefined constant for the number 3. Used by g functions */
#define THREE 3
/** Predefined constant for the number 5. Used by g functions. */
#define FIVE 5
/** Predefined constant for the number 7. Used by g functions. */
#define SEVEN 7
/**
 * Length of the final hash value. Also number of bits in an
 * unsigned integer.
 */
#define HASH_LENGTH 32
/**
 * Round Three is defined as being between 32 and 48. The lower bound is taken care
 * of so this constant represents the upper bound for round 3.
 */
#define ROUND_3_BOUND 48

/** Representation for the state of the MD5 computation.  It's just 4
    unsigned 32-bit integers. Client code can create an instance
    (statically, on the stack or on the heap), but initState() needs
    to initialize it before it can be used. */
typedef struct {
  /** Field A from the MD5 state.  This comment and the ones below
      aren't particularly meaningful, because there isn't really a
      particular mening for each of these fields. */
  unsigned int A;
  
  /** Field B from the MD5 state.  */
  unsigned int B;

  /** Field B from the MD5 state.  */
  unsigned int C;
  
  /** Field B from the MD5 state.  */
  unsigned int D;
} MD5State;

#endif

/**
 * Initializes the state of the MD5State struct with the four
 * predetermined values.
 * @param state MS5State struct pointer for which to initialize fields
 */
extern void initState(MD5State *state);

/**
 * In order for the algorithm to work, the buffer must be a multiple of
 * 64 bytes, this method pads the input so it is a multiple of 64 bytes.
 * @param b pointer to buffer to pad
 */
extern void padBuffer(Buffer *b);

/**
 * Takes the buffer as a 64 byte array, casts this array into 16 integers, and
 * calls upon the md5Iteration function to perform 64 iterations, then it updates
 * the state of the MD5State struct to be the completed values of the fields added
 * to the original values of the fields.
 * @param data 64 byte char array of the buffer
 * @param state pointer to the MD5State struct whose values are to be updated
 */
extern void md5Block(unsigned char data[MD5_BLOCK], MD5State *state);

/**
 * Prints the hex values of each unsigned integer. Reverses the bytes
 * so the unsigned integer is diplayed little-endian.
 * @param val unsigned int value to print in little-endian hex
 */
extern void printBytes(unsigned int val);
