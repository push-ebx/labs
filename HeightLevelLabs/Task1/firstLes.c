#include <stdio.h>

int main()
{
  char str1[1000];
  int c;
  int len1 = 0, len2 = 0;
  int flag = 1;

  while ((c = getchar()) != '\n')
  {
    str1[len1] = c;
    len1++;
  }

  while ((c = getchar()) != '\n')
  {
    if (str1[len2] != c)
      flag = 0;
    len2++;
  }
  
  printf((len1 > len2) ? "len1 > len2\n" : ((len2 > len1) ? "len2 > len1\n" : "le12 = len1\n"));
  printf(flag ? "Equals" : "Not Equals");
  return 0;
}