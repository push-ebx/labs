#include <stdio.h>

int main()
{
  char prev;
  char c;
  int count = 0;
  while ((c = getchar()) != '\n')
  {
    if (prev == 'c' && c == 'd')
      count++;
    prev = c;
  }

  printf("%d", count);
  return 0;
}