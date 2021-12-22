#include <stdio.h>
int main()
{
  FILE *input;
  FILE *output;

  char current_line[1000];
  char *p;

  input = fopen("input.txt", "rt");
  if (!input)
    return 0;

  output = fopen("output.txt", "wt");
  if (!output)
    return 0;

  char result_line[1000];
  int pos = 0;

  while (!feof(input))
  {
    p = fgets(current_line, 1000, input);
    if (!p)
      break;

    while (*p != '\0')
    {
      if ((int)*p >= 65 && (int)*p <= 90)
      {
        result_line[pos] = *p;
        pos++;
      }
      p++;
    }
    result_line[pos] = '\n';
    pos = 0;
    fputs(result_line, output);

    for (int i = 0; i < sizeof(result_line) / sizeof(result_line[0]); i++)
    {
      result_line[i] = '\0';
    }
  }
  fclose(input);
  fclose(output);
  return 0;
}