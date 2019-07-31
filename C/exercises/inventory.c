#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// One inch equals this many meters.
#define INCHES_TO_METERS 0.0254

// Representation for for an imperial measurement, as a length in
// inches.  The length is represented as a mixed numeral, with an
// integer number of inches and a simple fraction represented as
// numerator and denominator.  So, in inches, the length would be
// equivalent to inches + numerator / denominator.
typedef struct {
  int inches;
  int numerator;
  int denominator;
} ImperialLength;

// Remptesentation for a type of item in our inventory, with
// a length that's measured in metric or imperial units.
typedef struct {
  // Unique ID for this type of item.
  int sku;

  // Enumeration to indicate whether this is a metric or an imperial
  // measurement.
  enum { metric, imperial } mtype;

  // Length, represented in either imperial units (as an instance of
  // ImperialLength) or metric (as a double).  The mtype field says
  // which element of this union we're using.
  union {
    double mval;
    ImperialLength ival;
  } length;
} Item;

// Print a usage message, and exit unsuccessfully.
static void usage()
{
  fprintf( stderr, "usage: inventory <inventory-file>\n" );
  exit( EXIT_FAILURE );
}

// Complain if the inventory file is bad.
static void invalid()
{
  fprintf( stderr, "Invalid inventory file\n" );
  exit( EXIT_FAILURE );
}

// Comparison function for sorting items.
int itemComp( void const *pA, void const *pB )
{
  // These two pointers are really pointers to items.
  Item const *itemA = (Item *) pA;
  Item const *itemB = (Item *) pB;

  // Compare the length of the items pointed to by itemA and itemB.
  double impA;
  double impB;
  if (itemA->mtype == imperial) {
      double fraction = (double)itemA->length.ival.numerator / (double)itemA->length.ival.denominator;
      fraction *= INCHES_TO_METERS;
      impA = itemA->length.ival.inches * INCHES_TO_METERS;
      impA += fraction;
  }
  if (itemB->mtype == imperial) {
      double fraction = (double)itemB->length.ival.numerator / (double)itemB->length.ival.denominator;
      fraction *= INCHES_TO_METERS;
      impB = itemB->length.ival.inches * INCHES_TO_METERS;
      impB += fraction;
  }
  if (itemA->mtype == metric && itemB->mtype == metric) {
      if (itemA->length.mval > itemB->length.mval) {
          return 1;
      } else {
          return -1;
      }
  } else if (itemA->mtype == imperial && itemB->mtype == imperial) {
      if (impA > impB) {
          return 1;
      } else {
          return -1;
      }
  } else if (itemA->mtype == metric && itemB->mtype == imperial) {
      if (itemA->length.mval > impB) {
          return 1;
      } else {
          return -1;
      }
  } else if (itemA->mtype == imperial && itemB->mtype == metric) {
      if (impA > itemB->length.mval) {
          return 1;
      } else {
          return -1;
      }
  }
  return 0;
}

int main( int argc, char *argv[] )
{
  // Validate input arguments, and open the inventory input file.
  if ( argc != 2 )
    usage();

  FILE *fp = fopen( argv[ 1 ], "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open input file: %s\n", argv[ 1 ] );
    exit( EXIT_FAILURE );
  }

  // Read the inventory, first the number of items.
  int icount;
  if ( fscanf( fp, "%d", &icount ) != 1 )
    invalid();

  // Then, read all the inventory items.
  Item *ilist = (Item *) malloc( icount * sizeof( Item ) );
  for ( int i = 0; i < icount; i++ ) {
    // Read an item and store it in element i of ilist.
    int sk;
    char denominator;
    double len;
    int inch;
    int num;
    int den;
    fscanf(fp, "%d%*c%c", &sk, &denominator);
    ilist[i].sku = sk;
    if (denominator == 'm') {
        ilist[i].mtype = metric;
        fscanf(fp, "%lf", &len);
        ilist[i].length.mval = len;
    } else if (denominator == 'i') {
        ilist[i].mtype = imperial;
        fscanf(fp, "%d%d%*c%*c%*c%d", &inch, &num, &den);
        ilist[i].length.ival.inches = inch;
        ilist[i].length.ival.numerator = num;
        ilist[i].length.ival.denominator = den;
    }
  }

  // Sort the items by length.
  qsort( ilist, icount, sizeof( Item ), itemComp );

  // Print out the sorted list, in the same format as the input.
  printf( "%d\n", icount );
  for ( int i = 0; i < icount; i++ ) {
    // Print item i from ilist, with a real-valued length if it's metric, or
    // as a mixed numeral if it's metric.
    printf("%d ", ilist[i].sku);
    if (ilist[i].mtype == metric) {
        printf("%f\n", ilist[i].length.mval);
    } else {
        printf("%d %d / %d\n", ilist[i].length.ival.inches, ilist[i].length.ival.numerator, ilist[i].length.ival.denominator);
    }
  }

  // Free the resources and exit successfully.
  free( ilist );
  fclose( fp );
  return EXIT_SUCCESS;
}
