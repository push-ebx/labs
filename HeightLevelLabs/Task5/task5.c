#include <stdio.h>
#include <stdlib.h>

int main()
{
  int array[] = {3, 0, -1, 5, -45, 10, 1, -3, 2, 2, 4, -9};
  int len = sizeof(array) / sizeof(array[0]);
  int *res;
  res = malloc(sizeof(int) * len);

  for (int i = 0; i < len; i++)
    (array[i] < 0) ? (res[i] = 0) : (res[i] = array[i]);

  char **result = (char **)malloc(sizeof(char *) * len);

  for (size_t i = 0; i < len; i++)
    result[i] = malloc(sizeof(char) * res[i]);

  for (size_t i = 0; i < len; i++)
  {
    for (size_t j = 0; j < res[i]; j++)
      printf("a");
    if (res[i])
      printf("\n");
  }
  return 0;
}