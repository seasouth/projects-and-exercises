#include <iostream>
#include <cstdio>
using namespace std;

void a(int i)
{
  printf("In procedure a: i = %d\n", i);
  a(i);
}

main()
{
  a(10);
}
