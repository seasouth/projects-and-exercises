#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int imult(int a, int b)
{
  int product;

  product = 0;

  while (b > 0) {
    product += a;
    b--;
  }
  return product;
}

main(int argc, char **argv)
{
  if (argc != 3) {
    fprintf(stderr, "usage: mult1 a b\n");
    exit(1);
  }
  
  printf("%d\n", imult(atoi(argv[1]), atoi(argv[2])));
}
