// Exercise to read a sequence of doubles stored in binary format from
// a file, and then write the cosine of each to a file (in text)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main( int argc, char *argv[] )
{
  // Open the the input file in binary mode
  FILE *binIn = fopen("doubles.bin", "rb");

  // Open the the output file in text mode
  FILE *textOut = fopen("output.txt", "w");

  // Read double values from the inupt file using fread().  Use an array
  // that's large enough to hold 100 values, and use the return value
  // of fread to tell how many you successfully read.
  double values[ 100 ];
  int len;
  int count = 0;
  while (count <= 100 && (len = fread(values, sizeof(double), sizeof(values), binIn)) != 0) {
      count = len;
  }

  // Loop over the list of values and print the cosine of each
  // to the output file, one value per line with 4 fractional digits
  // of precision.
  for (int i = 0; i < count; i++) {
      double value = values[i];
      double co = cos(value);
      fprintf(textOut, "%.4f\n", co);
  }

  // Close both of the files.
  fclose(binIn);
  fclose(textOut);

  return 0;
}
