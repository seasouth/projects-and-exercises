/**
 * @file banner.c
 * @author Cole Southern (csouthe)
 *
 * This program reads a message from a file, considers validity of
 * message, and if valid, writes the message as an array of integers
 * representing intensity of pixels for a pgm file, and writes the
 * array to a pgm file to display message.
 */

#include "util.h"
#include "glyph.h"
#include <stdio.h>
#include <stdlib.h>

/** Maximum pixel intensity in pgm file. */
#define MAX_INTENSITY 9

/**
 * Writes a given array to a pgm file, after specifying pgm parameters. Array represents
 * information about a message including how each character looks in message. Image
 * will display message in pgm format.
 * @param rows number of rows in the array
 * @param cols number of columns in the array
 * @param img array containing intensity of pixels to represent a message
 */
void writeImage(int rows, int cols, short img[rows][cols])
{
    printf("P2\n");
    printf("%d %d\n", cols, rows);
    printf("%d\n", MAX_INTENSITY);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - 1) {
                printf("%d ", img[i][j]);
            } else {
                printf("%d", img[i][j]);
            }
        }
        printf("\n");
    }
}
/**
 * Program starting point, creates char array to store message and check for
 * message validity. If valid, passes each character of array to writeImage method
 * to write the message into a pgm file.
 * @return 0 if program exits succesfully and positive integer if not
 */
int main()
{
    char message[MAX_MESSAGE];
    int length = readMessage(message);
    if (length == 0) {
        return INVALID_LENGTH;
    } else if (length == -1) {
        return INVALID_CHAR;
    }
    int rows = GLYPH_HEIGHT;
    int cols = length * GLYPH_WIDTH;
    short img[rows][cols];
    short glyph[GLYPH_HEIGHT][GLYPH_WIDTH];
    int h = 0;
    for (int i = 0; i < length; i++) {
        getGlyph(message[i], glyph);
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < GLYPH_WIDTH; k++) {
                img[j][h] = glyph[j][k];
                h++;
            }
            h = i * GLYPH_WIDTH;
        }
        h += GLYPH_WIDTH;
    }
    writeImage(rows, cols, img);
    return EXIT_SUCCESS;
    
}
