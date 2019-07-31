/**
 * @file chop.c
 * @author Cole Southern (csouthe)
 *
 * This program reads from standard input and/or a file to obtain text,
 * edits the text according to command line argument specifications, and
 * writes the edited text either to the standard output or to an output
 * file, however the user specifies through command line arguments.
 */

#include "text.h"
#include "edit.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEFAULT_ARGC 3

/**
 * Checks for the validity of input file handed in from main from command
 * line arguments. If the number of characters in a line is greater than
 * 101, or if there are more than 10,000 lines, it writes an appopriate
 * message to standard error and passes int of 1 to main to indicate the
 * file is invalid.
 * @param *cpy pointer to the file specified by command line argument
 * @return returns integer representing file validity (0 if valid, 1 if not)
 */
int validFile(FILE *cpy)
{
    char (*copy)[MAX_CHARS];
    copy = (char (*)[MAX_CHARS]) malloc(MAX_LINES * MAX_CHARS * sizeof(char));
    int line = 0;
    int col = 0;
    char ch;
    while (fscanf(cpy, "%c", &ch) == 1) {
        copy[line][col++] = ch;
        if (ch == '\n') {
            line++;
            col = 0;
        }
    }
    fclose(cpy);
    if (line > MAX_LINES) {
        free(copy);
        fprintf(stderr, "Too many lines\n");
        return 1;
    }
    for (int i = 0; i < line; i++) {
        if (strlen(copy[i]) > MAX_CHARS) {
            free(copy);
            fprintf(stderr, "Line too long\n");
            return 1;
        }
    }
    free(copy);
    return 0;
}

/**
 * Program starting point. Accepts command line arguments for input
 * file (optional) and editing specifications. If input filename is
 * given, it checks for file validity and hands it to various functions
 * to make specified edits, then passes to a function to write the
 * result to an output file, if this is specified by command line
 * arguments.
 * @param int argc number of command line arguments
 * @param char *argv[] array of command line arguments
 * @return returns exit status (0 if successful, 1 if not)
 */
int main(int argc, char *argv[])
{
    if (strcmp(argv[argc - 2], "-")) {
        FILE *cpy = fopen(argv[argc - 2], "r");
        if (!cpy) {
            fprintf(stderr, "%s: %s\n", "Can't open file", argv[argc - 2]);
            return 1;
        }
        int valid = validFile(cpy);
        if (valid == 1) {
            return 1;
        }
        if (valid == 2) {
            fprintf(stderr, "Can't open file\n");
            return 1;
        }
        FILE *read = fopen(argv[argc - 2], "r");
        readFile(read);
        fclose(read);
    } else {
        text = (char (*)[MAX_CHARS]) malloc(MAX_LINES * MAX_CHARS * sizeof(char));
        int line = 0;
        int col = 0;
        char ch;
        while (scanf("%c", &ch) == 1) {
            text[line][col++] = ch;
            if (ch == '\n') {
                line++;
                col = 0;
            }
        }
        lines = line;
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "lines") == 0) {
            if (atoi(argv[i + 1]) > atoi(argv[i + 2])) {
                fprintf(stderr, "invalid arguments\n");
                fprintf(stderr, "usage: chop command* (infile|-) (outfile|-)\n");
                return 1;
            }
            removeLines(atoi(argv[i + 1]), atoi(argv[i + 2]));
        } else if (strcmp(argv[i], "line") == 0) {
            removeLines(atoi(argv[i + 1]), atoi(argv[i + 1]));
        } else if (strcmp(argv[i], "cols") == 0) {
            if (atoi(argv[i + 1]) > atoi(argv[i + 2])) {
                fprintf(stderr, "invalid arguments\n");
                fprintf(stderr, "usage: chop command* (infile|-) (outfile|-)\n");
                return 1;
            }
            removeCols(atoi(argv[i + 1]), atoi(argv[i + 2]));
        } else if (strcmp(argv[i], "col") == 0) {
            removeCols(atoi(argv[i + 1]), atoi(argv[i + 1]));
        } else {
            if (i == 1 && argc > DEFAULT_ARGC) {
                fprintf(stderr, "invalid arguments\n");
                fprintf(stderr, "usage: chop command* (infile|-) (outfile|-)\n");
                return 1;
            }
        }
    }
    
    if (strcmp(argv[argc - 1], "-")) {
        FILE *write = fopen(argv[argc - 1], "w");
        writeFile(write);
        fclose(write);
    } else {
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < strlen(text[i]); j++) {
                printf("%c", text[i][j]);
            }
        }
    }
    return EXIT_SUCCESS;
}
