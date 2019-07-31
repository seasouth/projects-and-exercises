#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int factorial(int i)
{
  int f;

  f = 1;
  while (i > 0) {
    f *= i;
    i--;
  }
}

main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: fact1 n\n");
    exit(1);
  }
  
  printf("%d\n", factorial(atoi(argv[1])));
}
