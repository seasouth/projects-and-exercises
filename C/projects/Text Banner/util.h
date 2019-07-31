/**
 * @file util.h
 * @author Cole Southern (csouthe)
 *
 * Header file for util.c, defines preprocessor macro constants
 * and provides prototypes for functions.
 */

#include "glyph.h"

/** Max permitted message size. */
#define MAX_MESSAGE 60
/** Error message for invalid length of message. */
#define INVALID_LENGTH 101
/** Error message for invalid characters in message. */
#define INVALID_CHAR 100
/** Lower bound for ascii range permitted. */
#define MIN_ASCII 32
/** Higher bound for ascii range permitted. */
#define MAX_ASCII 126

/**
 * Prototype for getGlyph, which generates an array representing the
 * character as a series of pixels each with an intensity value to display
 * character.
 * @param ch character to be converted to array of pixels
 * @param glyph array of pixels representing each character.
 */
extern void getGlyph(char ch, short glyph[GLYPH_HEIGHT][GLYPH_WIDTH]);
/**
 * Prototype for readMessage, which reads an array of chars and ensures the input is valid. Returns
 * the number of chars in array if valid, returns 0 or 1 if invalid.
 * @param message represents char array containing message
 * @return int representing length of message and validity of message
 */
extern int readMessage(char message[MAX_MESSAGE]);
