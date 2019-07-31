#include <iostream>
#include <cstdio>
using namespace std;

void a(int i)
{
  printf("In procedure a: i = %d\n", i);
  if (i == 10) a(9);
}

main()
{
  a(10);
}
