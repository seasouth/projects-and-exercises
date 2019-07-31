/**
 * @file hash.c
 * @author Cole Southern
 *
 * This file is the starting point for the hash program and contains the
 * main function. It delegates most of the responsibility for file handling,
 * hashing, and printing the hashed value.
 */

#include "buffer.h"
#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Program starting point, verifies file is valid, and if it is, delegates
 * tasks to the other components to create an md5 hash value of the given input.
 * @param argc number of command line arguments
 * @param argv array of pointers to the command line arguments
 * @return EXIT_SUCCESS if no errors, and EXIT_FAILURE if an error occurred.
 */
int main(int argc, char *argv[])
{
    char *textfile = "txt";
    char *binfile = "bin";
    if (argc < 2) {
        fprintf(stderr, "usage: hash <filename>\n");
        return EXIT_FAILURE;
    }
    if (strcmp(textfile, argv[1]) == 0 && strcmp(binfile, argv[1]) == 0) {
        fprintf(stderr, "usage: hash <filename>\n");
        return EXIT_FAILURE;
    }
    Buffer *b = readFile(argv[argc - 1]);
    if (b == NULL) {
        fprintf(stderr, "Can't open file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    MD5State *state = (MD5State *)malloc(sizeof(MD5State));
    initState(state);
    padBuffer(b);
    unsigned char *datacpy = b->data;
    for (int i = 0; i < b->len / MD5_BLOCK; i++) {
        unsigned char data[MD5_BLOCK];
        memcpy(data, datacpy, MD5_BLOCK * sizeof(unsigned char));
        md5Block(data, state);
        datacpy += MD5_BLOCK;
    }

    printBytes(state->A);
    printBytes(state->B);
    printBytes(state->C);
    printBytes(state->D);
    printf("\n");
    freeBuffer(b);
    free(state);
    return EXIT_SUCCESS;
}
