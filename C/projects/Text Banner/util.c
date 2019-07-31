/**
 * @file util.c
 * @author Cole Southern (csouthe)
 *
 * This program provides functionality for reading a message from file,
 * checking for validity of message, and converting each char into an array
 * that can be used for large display of each character in the message.
 */

#include "util.h"
#include "glyph.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Reads an array of chars and ensures the input is valid. Returns
 * the number of chars in array if valid, returns 0 or 1 if invalid.
 * @param message represents char array containing message
 * @return int representing length of message and validity of message
 */
int readMessage(char message[MAX_MESSAGE])
{
    int i = 0;
    while (scanf("%c", &message[i]) == 1) {
        if (i == MAX_MESSAGE + 1) {
            return 0;
        }
        if (message[i] != '\n' && (message[i] < MIN_ASCII || message[i] > MAX_ASCII)) {
            return -1;
        }
        if (message[i] == '\n') {
            return i;
        }
        i++;
    }
    if (message[i - 1] != '\n') {
        return -1;
    }
    return i;
}

/**
 * Generates an array representing the character as a series of pixels
 * each with an intensity value to display character.
 * @param ch character to be converted to array of pixels
 * @param glyph array of pixels representing each character.
 */
void getGlyph(char ch, short glyph[GLYPH_HEIGHT][GLYPH_WIDTH])
{
    int ascii = (ch - MIN_ASCII) * GLYPH_HEIGHT;
    for (int i = 0; i < GLYPH_HEIGHT; i++) {
        for (int j = 0; j < GLYPH_WIDTH; j++) {
            glyph[i][j] = shapes[ascii + i][j];
        }
    }
}
