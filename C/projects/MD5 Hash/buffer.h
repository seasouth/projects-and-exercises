/**
 * @file buffer.h
 * @author Cole Southern, David Sturgill
 *
 * Header file for buffer.c, which handles a text or bin file, creates a buffer,
 * and adds that file's contents in the form of bytes into this buffer. The buffer
 * contains the information which is to be hashed using the md5 algorithm. After
 * the buffer has been used, this program frees the buffer from heap allocated
 * memory.
 */

#ifndef _BUFFER_H_
#define _BUFFER_H_

/** Representation for the contents of an input file, copied to memory. */
typedef struct {
  /** Array of bytes from the file (not a string). */
  unsigned char *data;

  /** Number of currently used bytes in the data array. */
  unsigned int len;

  /** Capacity of the data array (it's typically over-allocated. */
  unsigned int cap;
} Buffer;

#endif

/**
 * Creates a Buffer struct and initializes the initial cap for the amount
 * of chars the buffer can contain.
 * @return Buffer returns a pointer to the buffer created
 */
extern Buffer *makeBuffer();

/**
 * Takes a buffer and a given byte and appends the byte to the buffer, increasing
 * the capacity of the buffer if necessary.
 * @param b pointer to buffer to append char to
 * @param byte char to append to given buffer
 */
extern void appendBuffer(Buffer *b, unsigned char byte);

/**
 * Buffer is heap allocated, this method frees the heap allocated memory.
 * @param b pointer to buffer to free from heap
 */
extern void freeBuffer(Buffer *b);

/**
 * Reads contents of given file and creates a buffer to store contents into,
 * then stores contents into buffer until end of file is reached.
 * @param filename pointer to string containing filename
 * @return pointer to Buffer created from contents of file
 */
Buffer *readFile(const char *filename);
