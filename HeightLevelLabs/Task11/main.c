#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char c;
  char replace_str[5];
  char replace_c;
  FILE *input;
  FILE *output;

  input = fopen("input.txt", "r");
  output = fopen("output.txt", "w");

  gets(replace_str);
  if (!strcmp("tab", replace_str))
    replace_c = '\t';
  else if (!strcmp("enter", replace_str))
    replace_c = '\n';
  else
    replace_c = replace_str[0];

  while ((c = fgetc(input)) != EOF)
    if (c == ' ' || c == ',' || c == '.' || c == '!' || c == '?' || c == '\n')
      fputc(replace_c, output);
    else
      fputc(c, output);
  return 0;
}