#include <stdio.h>

// цифры заменить на слова
int main()
{
  char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  FILE *input;
  FILE *output;

  char cur_line[1000];
  char *p;

  input = fopen("input.txt", "rt");
  if (!input)
    return 0;

  output = fopen("output.txt", "wt");
  if (!output)
    return 0;

  char res_line[1000];
  int pos = 0;

  while (!feof(input))
  {
    p = fgets(cur_line, 1000, input);
    if (!p)
      break;

    while (*p != '\0')
    {
      if ((*p >= '0' && *p <= '9'))
      {
        for (int i = 0; numbers[(int)*p - 48][i] != '\0'; i++)
        {
          res_line[pos] = numbers[(int)(*p) - 48][i];
          pos++;
        }
      }
      else
      {
        res_line[pos] = *p;
        pos++;
      }
      p++;
    }

    pos = 0;
    fputs(res_line, output);
    for (int i = 0; i < sizeof(res_line) / sizeof(res_line[0]); i++)
    {
      res_line[i] = '\0';
    }
  }

  fclose(input);
  fclose(output);
  return 0;
}