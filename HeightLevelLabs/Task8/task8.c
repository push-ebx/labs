#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

int main()
{
  FILE *input;
  input = fopen("input.txt", "r+");

  char stack[MAX_LEN] = {0};
  char c;

  while ((c = fgetc(input)) != EOF)
  {
    if (c == '{' || c == '(' || c == '[')
      stack[strlen(stack)] = c;
    else if (stack[strlen(stack) - 1] == '{' && c == '}')
      stack[strlen(stack) - 1] = 0;
    else if (stack[strlen(stack) - 1] == '[' && c == ']')
      stack[strlen(stack) - 1] = 0;
    else if (stack[strlen(stack) - 1] == '(' && c == ')')
      stack[strlen(stack) - 1] = 0;
    else if (c == '}' || c == ']' || c == ')')
    {
      printf("%s", "Brackets are placed incorrectly\n");
      fclose(input);
      return 0;
    }
  }

  strlen(stack) == 0 ? printf("%s", "Brackets are placed correctly\n") : printf("%s", "Brackets are placed incorrectly\n");
  fclose(input);
  return 0;
}