/**
 * @file text.h
 * @author Cole Southern (csouthe)
 *
 * This is a header file for text.c, which reads from a file to create
 * a 2D char array representing the text given by the input. Once the
 * text representation is edited according to command line arguments,
 * this program writes the edited text into an output file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Max number of characters a line can store */
#define MAX_CHARS 101
/** Max number of lines of text to store */
#define MAX_LINES 10000

/** 2D char array of text representation. */
char (*text)[MAX_CHARS];
/** Number of lines in the array declared above. */
int lines;

/**
 * Reads text from a given file and stores it in the global test representation.
 * @param *fp pointer to file name to read in from
 */
extern void readFile(FILE *fp);
/**
 * Writes out the text from the global text representation to the given output file.
 * @param *fp pointer to file name to write out to
 */
extern void writeFile(FILE *fp);
