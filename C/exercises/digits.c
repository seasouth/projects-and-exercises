// Do some I/O and math with unsigned types.
/**
    @author csouthe (Cole Southern)
*/
#include <stdlib.h>
#include <stdio.h>

/**
   Add up all the digits in the value, x, and return the sum.
*/
unsigned int digitSum( unsigned long x )
{
  unsigned long sum = 0;
  while (x > 10) {
      unsigned long add = x % 10;
      sum += add;
      x = x / 10;
  }
  sum += x;
  return sum;
}

int main()
{
  // Range of values we're supposed to check.
  unsigned long low, high;

  // Target sum we're supposed to look for.
  unsigned int target;

  // Read the range of values from the user.
  int matches = scanf("%lu%lu", &low, &high);
  if (matches != 2) {
      return EXIT_FAILURE;
  }

  // Read the digit sum we're supposed to look for.
  matches = scanf("%u", &target);
  if (matches != 1) {
      return EXIT_FAILURE;
  }

  // Check all values from low up to high (inclusive), and report the ones
  // that have the given digit sum.
  for (unsigned long i = low; i <= high; i++) {
      if (target == digitSum(i)) {
          unsigned long matchesTarget = i;
          printf("%lu%s", matchesTarget, "\n");
      }
  }

  return EXIT_SUCCESS;
}
