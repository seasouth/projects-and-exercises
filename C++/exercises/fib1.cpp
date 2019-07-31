#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int fibonacci(int n)
{
  if (n <= 1) return 1;
  return fibonacci(n-1) + fibonacci(n-2);
  
  
}

main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: fib1 n\n");
    exit(1);
  }
  
  printf("%d\n", fibonacci(atoi(argv[1])));
}
