/**
 * @file md5.c
 * @author Cole Southern, David Sturgill
 *
 * Stores he md5 struct which contains the four field states which will be
 * modified. This file contains the bulk of the algorithm involving hashing
 * the contents of the given input file. Also, this file contains the shift
 * and noise arrays which are included in the algorithm at each iteration.
 */

#include "md5.h"
#include "buffer.h"
#include <stdio.h>

/* Mechanism to conditionally expose static functions to other components.  For
   production, we can make make them static, but for testing we can disable
   the static keyword and expose functions to the test driver. */
#ifdef TESTABLE
#define test_static
#else
#define test_static static
#endif

/** Within each iteration, how many bits left do we rotate the a value? */
static int shift[ MD5_BLOCK ] =
  { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };

/** Constants, to mix in some random-looking bits during the MD5
    calculation.  These are computed from the sin() function.  They're
    examples of what might be called "Nothing-Up-My-Sleeve"
    numbers. */
static unsigned int noise[ MD5_BLOCK ] =
  { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

/**
 * Initializes the state of the MD5State struct with the four
 * predetermined values.
 * @param state MS5State struct pointer for which to initialize fields
 */
void initState(MD5State *state)
{
    state->A = 0x67452301;
    state->B = 0xefcdab89;
    state->C = 0x98badcfe;
    state->D = 0x10325476;
}

/**
 * In order for the algorithm to work, the buffer must be a multiple of
 * 64 bytes, this method pads the input so it is a multiple of 64 bytes.
 * @param b pointer to buffer to pad
 */
void padBuffer(Buffer *b)
{
    int len = b->len;
    appendBuffer(b, 0x80);
    while (b->len % MD5_BLOCK < MD5_BLOCK - BYTE) {
        appendBuffer(b, 0x00);
    }
    unsigned int size = len * BYTE;
    unsigned int mask = MD5_BLOCK * HALF_BYTE - 1;
    for (int i = 0; i < BYTE; i++) {
        unsigned char byte = (unsigned char) (size & mask);
        size = size >> BYTE;
        appendBuffer(b, byte);
    }
}

/**
 * In the first round, this is the f function that will be used.
 * @param b unsigned integer to calculate included unsigned int value
 * @param c unsigned integer to calculate included unsigned int value
 * @param d unsigned integer to calculate included unsigned int value
 * @return unsigned int to include in hashing algorithm
 */
test_static unsigned int fVersion0(unsigned int b, unsigned int c, unsigned int d)
{
    unsigned int ret = ((b & c) | ((~b) & d));
    return ret;
}

/**
 * In the second round, this is the f function that will be used.
 * @param b unsigned integer to calculate included unsigned int value
 * @param c unsigned integer to calculate included unsigned int value
 * @param d unsigned integer to calculate included unsigned int value
 * @return unsigned int to include in hashing algorithm
 */
test_static unsigned int fVersion1(unsigned int b, unsigned int c, unsigned int d)
{
    unsigned int ret = ((b & d) | (c & (~d)));
    return ret;
}

/**
 * In the third round, this is the f function that will be used.
 * @param b unsigned integer to calculate included unsigned int value
 * @param c unsigned integer to calculate included unsigned int value
 * @param d unsigned integer to calculate included unsigned int value
 * @return unsigned int to include in hashing algorithm
 */
test_static unsigned int fVersion2(unsigned int b, unsigned int c, unsigned int d)
{
    unsigned int ret = (b ^ c ^ d);
    return ret;
}

/**
 * In the fourth round, this is the f function that will be used.
 * @param b unsigned integer to calculate included unsigned int value
 * @param c unsigned integer to calculate included unsigned int value
 * @param d unsigned integer to calculate included unsigned int value
 * @return unsigned int to include in hashing algorithm
 */
test_static unsigned int fVersion3(unsigned int b, unsigned int c, unsigned int d)
{
    unsigned int ret = (c ^ (b | (~d)));
    return ret;
}

/**
 * In the first round, this is the g function that will be used.
 * @param idx integer representing current iteration
 * @return offset of unsigned int in noise array to include in algorithm
 */
test_static int gVersion0(int idx)
{
    return idx;
}

/**
 * In the second round, this is the g function that will be used.
 * @param idx integer representing current iteration
 * @return offset of unsigned int in noise array to include in algorithm
 */
test_static int gVersion1(int idx)
{
    return ((FIVE * idx) + 1) % WORD;
}

/**
 * In the third round, this is the g function that will be used.
 * @param idx integer representing current iteration
 * @return offset of unsigned int in noise array to include in algorithm
 */
test_static int gVersion2(int idx)
{
    return ((THREE * idx) + FIVE) % WORD;
}

/**
 * In the fourth round, this is the g function that will be used.
 * @param idx integer representing current iteration
 * @return offset of unsigned int in noise array to include in algorithm
 */
test_static int gVersion3(int idx)
{
    return ((SEVEN * idx) % WORD);
}

/**
 * This functions accepts a value and rotates it the given int number of
 * bits. There is wrapping at the end, so the higher order bits being shifted
 * will wrap to the lower order bytes.
 * @param value unsigned integer to be rotated left
 * @param s int indicating number of bits to shift left
 * @return unsigned integer of left rotated value
 */
test_static unsigned int rotateLeft(unsigned int value, int s)
{
    unsigned int wrap = value;
    wrap = wrap >> (HASH_LENGTH - s);
    value = value << s;
    value = value | wrap;
    return value;
}

/**
 * This function represents one iteration of the md5 hashing algorithm. It accepts
 * four unsigned integers and the iteration number, updates these values, and returns
 * the updated values.
 * @param data array of 16 unsigned integers which represent the data to hash
 * @param a pointer to the A field in the md5 state
 * @param b pointer to the B field in the md5 state
 * @param c pointer to the C field in the md5 state
 * @param d pointer to the D field in the md5 state
 * @param i int representing iteration number
 */
test_static void md5Iteration(unsigned int data[MD5_BLOCK], unsigned int *a, unsigned int *b,
        unsigned int *c, unsigned int *d, int i)
{
    unsigned int (*f[HALF_BYTE])(unsigned int b, unsigned int c, unsigned int d);
    f[0] = fVersion0;
    f[1] = fVersion1;
    f[2] = fVersion2;
    f[THREE] = fVersion3;

    int (*g[HALF_BYTE])(int idx);
    g[0] = gVersion0;
    g[1] = gVersion1;
    g[2] = gVersion2;
    g[THREE] = gVersion3;

    int gfunction = 0;
    int ffunction = 0;
    if (i < WORD) {
        ffunction = 0;
        gfunction = 0;
    } else if (i < HASH_LENGTH) {
        ffunction = 1;
        gfunction = 1;
    } else if (i < ROUND_3_BOUND) {
        ffunction = 2;
        gfunction = 2;
    } else if (i < MD5_BLOCK) {
        ffunction = THREE;
        gfunction = THREE;
    }

    *a += f[ffunction](*b, *c, *d);
    *a += data[g[gfunction](i)];
    *a += noise[i];
    *a = rotateLeft(*a, shift[i]);
    *a += *b;

    unsigned int temp = *d;
    *d = *c;
    *c = *b;
    *b = *a;
    *a = temp;
}

/**
 * Takes the buffer as a 64 byte array, casts this array into 16 integers, and
 * calls upon the md5Iteration function to perform 64 iterations, then it updates
 * the state of the MD5State struct to be the completed values of the fields added
 * to the original values of the fields.
 * @param data 64 byte char array of the buffer
 * @param state pointer to the MD5State struct whose values are to be updated
 */
void md5Block(unsigned char data[MD5_BLOCK], MD5State *state)
{
    unsigned int a = state->A;
    unsigned int b = state->B;
    unsigned int c = state->C;
    unsigned int d = state->D;

    unsigned int *convert = (unsigned int *) data;

    for (int i = 0; i < MD5_BLOCK; i++) {
        md5Iteration(convert, &a, &b, &c, &d, i);
    }

    state->A += a;
    state->B += b;
    state->C += c;
    state->D += d;
}

/**
 * Prints the hex values of each unsigned integer. Reverses the bytes
 * so the unsigned integer is diplayed little-endian.
 * @param val unsigned int value to print in little-endian hex
 */
void printBytes(unsigned int val)
{
    unsigned char mask = 0xff;
    for (int i = 0; i < HALF_BYTE; i++) {
        unsigned char byte = mask & val;
        val = val >> BYTE;
        if (byte < 0x10) {
            printf("%X", 0x0);
        }
        printf("%X", byte);
    }
}
