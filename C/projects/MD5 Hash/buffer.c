/**
 * @file buffer.c
 * @author Cole Southern, David Sturgill
 *
 * This file handles a text or bin file, creates a buffer, and adds that files
 * contents in the form of bytes into this buffer. The buffer contains the
 * information which is to be hashed using the md5 algorithm. After the buffer has
 * been used, this program frees the buffer from heap allocated memory.
 */

#include "buffer.h"
#include "md5.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAP 3

/**
 * Creates a Buffer struct and initializes the initial cap for the amount
 * of chars the buffer can contain.
 * @return Buffer returns a pointer to the buffer created
 */
Buffer *makeBuffer()
{
    Buffer *b = (Buffer *)malloc(sizeof(Buffer));
    b->len = 0;
    b->cap = INITIAL_CAP;
    b->data = (unsigned char *)malloc(INITIAL_CAP * sizeof(unsigned char));
    return b;
}

/**
 * Takes a buffer and a given byte and appends the byte to the buffer, increasing
 * the capacity of the buffer if necessary.
 * @param b pointer to buffer to append char to
 * @param byte char to append to given buffer
 */
void appendBuffer(Buffer *b, unsigned char byte)
{
    if (b->len >= b->cap) {
        b->cap *= 2;
        b->data = (unsigned char *)realloc(b->data, b->cap * sizeof(unsigned char));
    }
    b->data[b->len++] = byte;
}

/**
 * Buffer is heap allocated, this method frees the heap allocated memory.
 * @param b pointer to buffer to free from heap
 */
void freeBuffer(Buffer *b)
{
    free(b->data);
    free(b);
}

/**
 * Reads contents of given file and creates a buffer to store contents into,
 * then stores contents into buffer until end of file is reached.
 * @param filename pointer to string containing filename
 * @return pointer to Buffer created from contents of file
 */
Buffer *readFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }
    unsigned char byte;
    Buffer *b = makeBuffer();
    while (fscanf(fp, "%c", &byte) == 1) {
        appendBuffer(b, byte);
    }
    fclose(fp);
    return b;
}
