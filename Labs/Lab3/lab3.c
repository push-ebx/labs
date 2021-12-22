#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *input;
  FILE *output;

  input = fopen("input.txt", "rt");
  if (!input)
    return 0;

  output = fopen("output.txt", "wt");
  if (!output)
    return 0;

  char current_line[1000];
  char *p;
  int i = 0;
  char temp[1000];
  int count_rows = 0;

  while (!feof(input)) // подсчитываем количество строк в файле
  {
    p = fgets(current_line, 1000, input);
    count_rows++;
  }

  char **lines = (char **)malloc(sizeof(char *) * count_rows); // массив строк файла
  fseek(input, 0, 0);

  while (!feof(input))
  {
    p = fgets(current_line, 1000, input);
    lines[i] = malloc(sizeof(char) * 1000);
    strcpy(lines[i], p);
    i++;
  }
  lines[i - 1][strlen(lines[i - 1]) - 1] = '\n';

  for (int i; i < count_rows - 1; i++)
  {
    for (int j = 0; j < count_rows - i - 1; j++)
    {
      if (strcmp(lines[j], lines[j + 1]) > 0)
      {
        strcpy(temp, lines[j + 1]);
        strcpy(lines[j + 1], lines[j]);
        strcpy(lines[j], temp);
      }
    }
  }

  for (int i = 0; i < count_rows; i++)
    fputs(lines[i], output);
    
  fclose(input);
  fclose(output);
  free(lines);
  return 0;
}