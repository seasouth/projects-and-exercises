/**
 * @file text.c
 * @author Cole Southern (csouthe)
 *
 * This program reads from a file to create a 2D char array representing
 * the text given by the input. Once the text representation is edited
 * according to command line arguments, this program writes the edited
 * text into an output file.
 */

#include "text.h"
#include "edit.h"

/**
 * Reads text from a given file and stores it in the global test representation.
 * @param *fp pointer to file name to read in from
 */
void readFile(FILE *fp)
{
    text = (char (*)[MAX_CHARS]) malloc(MAX_LINES * MAX_CHARS * sizeof(char));
    
    int line = 0;
    int col = 0;
    char ch;
    while (fscanf(fp, "%c", &ch) == 1) {
        text[line][col++] = ch;
        if (ch == '\n') {
            line++;
            col = 0;
        }
    }
    lines = line;
}

/**
 * Writes out the text from the global text representation to the given output file.
 * @param *fp pointer to file name to write out to
 */
void writeFile(FILE *fp)
{
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < strlen(text[i]); j++) {
            fprintf(fp, "%c", text[i][j]);
        }
    }
}
