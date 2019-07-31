#include <stdio.h>
#include <stdlib.h>

int main()
{
  // Check command-line arguments and open the input file.
  FILE *fp;
  if ( ( fp = fopen( "input.txt", "r" ) ) == NULL ) {
    fprintf( stderr, "Can't open file: input.txt\n" );
    exit( EXIT_FAILURE );
  }

  // Allocate a string with a small, initial capacity.
  int capacity = 5;
  char *buffer = (char *) malloc(capacity * sizeof(char)); //Initial call to malloc

  // Number of characters we're currently using.
  int len = 0;
  
  // Read from this file until we reach end-of-file, storing all characters
  // in buffer. Keep enlarging the buffer as needed until it contains the
  // contents of the whole file.  This took me 9 lines of code.
  // ...
  char ch;
  while (fscanf(fp, "%c", &ch) == 1) {
      if (len >= capacity) {
          capacity *= 2;
          char *newBuffer = (char *) malloc(capacity * sizeof(char));
          for (int i = 0; i < len; i++) {
              newBuffer[i] = buffer[i];
          }
          free(buffer);
          buffer = newBuffer;
      }
      buffer[len] = ch;
      len++;
  }

  // Print out the total size of the file, in characters.
  printf( "%d\n", len );

  // Print out the whole file, it's one big string.
  printf( "%s", buffer );

  // Don't leak memory or open files.
  // ...
  free(buffer);
  fclose(fp);

  return 0;
}
