#include <stdio.h>

int main()
{
  int array[] = {10, 0, -1, 12, -45, 49, 12, -3, 2, 23, 4, -9};
  int *p = array;
  int temp;
  int len = sizeof(array) / sizeof(array[0]);

  for (int i = 0; i < len; i += 2)
  {
    temp = *(p + i);
    *(p + i) = *(p + i + 1);
    *(p + i + 1) = temp;

    (*(p + i) < 0) ? (*(p + i) = 0) : 0;
    (*(p + i + 1) < 0) ? (*(p + i + 1) = 0) : 0;

    printf("%d ", *(p + i));
    if (len != i + 1)
      printf("%d ", *(p + i + 1));
  }
  printf("\n");
  return 0;
}