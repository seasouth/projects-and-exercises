int x = 10;
{
  x++;
  int x = 5;
  {
    printf( "%d\n", x );
  }
}
