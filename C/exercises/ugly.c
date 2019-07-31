// Same prime-detection strategy, but without any structured
// looping constructs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Report a list of prime values.
 */
int main( void )
{
  // Get the range of values we're supposed to test.
  unsigned int low, high;
  if ( scanf( "%d%d", &low, &high ) != 2 ) {
    printf( "Invalid input\n" );
    exit( EXIT_FAILURE );
  }
  
  // Write your own, ugly solution, using goto instead of structured looping.
  
  unsigned int val = 2;
  keepGoing:
  
  if (low <= high) {
      goto checkForPrime;
  } else {
      goto stopNow;
  }
  
  checkForPrime:
  
  if (low % val == 0) {
      low++;
      val = 2;
      goto keepGoing;
  } else {
      val++;
      if (val < low / 2) {
          goto checkForPrime;
      } else {
          printf("%u\n", low);
          val = 2;
          low++;
          goto keepGoing;
      }
      val++;
      goto checkForPrime;
  }
  
  stopNow:
  
  return EXIT_SUCCESS;
}
