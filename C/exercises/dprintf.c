#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


/** Append a given character, ch, to the end of a resizable array of
    characters.  The representation for the resizable array (str (the
    array), len (number of elements used) and cap (capacity)) are all
    passed by address, so this function can change them if needed. */
void append( char **str, int *len, int *cap, char ch )
{
  // Grow the array if it's not big enough.
  if ( *len + 1 >= *cap ) {
    *cap *= 2;
    *str = (char *) realloc( *str, *cap );
  }

  // Add ch to the end (a little ugly because str, len and cap are
  // all passed by address).
  (*str)[ (*len) ++ ] = ch;
}

char *d_printf( const char *fmt, ... )
{
  // Setup vararg processing
  // ...
  va_list ap;
  va_start(ap, fmt);

  // Resizable array of chars.
  int len = 0;
  int cap = 5;
  char *dest = (char *) malloc( cap );

  // Go through the format string.
  int pos = 0;
  while ( fmt[ pos ] ) {
    if ( fmt[ pos ] == '%' ) {
      // The current character is a %.  See if it's the start of %s,
      // %u or %% and handle it appropriately if it is.

      // ...
      if (fmt[pos + 1] && fmt[pos + 1] == 's') {
          char *str = va_arg(ap, char *);
          for (int i = 0; i < strlen(str); i++) {
              append(&dest, &len, &cap, str[i]);
          }
      } else if (fmt[pos + 1] && fmt[pos + 1] == 'u') {
          unsigned int a = va_arg(ap, unsigned int);
          int count = 0;
          while (a > 10) {
              unsigned int nextDigit = a % 10;
              char nextChar = (char)(nextDigit + 0x30);
              append(&dest, &len, &cap, nextChar);
              a /= 10;
              count++;
          }
          count++;
          char nextChar = (char)(a + 0x30);
          append(&dest, &len, &cap, nextChar);
          char temp[count];
          int reverse = 0;
          for (int i = len - 1; i >= count; i--) {
              temp[reverse++] = dest[i];
          }
          int reset = 0;
          for (int i = len - count; i < len; i++) {
              dest[i] = temp[reset++];
          }
      } else if (fmt[pos + 1] && fmt[pos + 1] == '%') {
          append(&dest, &len, &cap, '%');
      }
      // Advance past the next two characters in the format string,
      // unless we're at the end of the string already.
      if ( fmt[ pos + 1 ] )
        pos += 2;
      else
        pos += 1;
    } else {
      // Ordinary character, just copy it to the destination string.
      append( &dest, &len, &cap, fmt[ pos ] );
      pos += 1;
    }
  }

  // Null terminate the resulting string.
  append( &dest, &len, &cap, '\0' );
  
  // We're done processing arguments.
  // ...
  va_end(ap);

  // Return the string we made.
  return dest;
}

// Leave the rest of this unchanged.  This conditional compilation
// code will let me replace main() with a different test function for
// grading.
#ifndef OMIT_MAIN

int main()
{
  char *str;

  // Try a format string with no conversion specifications
  str = d_printf( "Testing\n" );
  printf( "%s", str );
  free( str );

  // A format string with a string conversion specification.
  char *name = "Bill";
  str = d_printf( "Hello %s.\n", name );
  printf( "%s", str );
  free( str );

  // A format string with an unsigned int conversion specification.
  unsigned int val = 72351;
  str = d_printf( "value: %u\n", val );
  printf( "%s", str );
  free( str );

  // A zero might be a special case when you print it.
  val = 0;
  str = d_printf( "A zero looks like \"%u\"\n", val );
  printf( "%s", str );
  free( str );

  // A format string that includes a literal % sign.
  val = 25;
  str = d_printf( "%u%% increase\n", val );
  printf( "%s", str );
  free( str );

  // A format string with a few different conversion specifications.
  str = d_printf( "Countdown: %u 4 %u %s %u 0. %s!\n",
                 5, 3, "2", 1, "blastoff" );
  printf( "%s", str );
  free( str );

  return EXIT_SUCCESS;
}

#endif
