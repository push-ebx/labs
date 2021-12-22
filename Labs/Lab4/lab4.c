#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
  HANDLE hStdout;
  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

  FILE *input;
  char current_line[1000];
  char *p;
  char words[100][50];
  int flag = 0;
  int pos = 0;
  int num_w = 0;

  input = fopen("input.c", "rt");

  if (!input)
    return 0;

  SetConsoleTextAttribute(hStdout, 7);

  while (!(feof(input)))
  {
    for (size_t i = 0; i < 100; i++)
      for (size_t j = 0; j < 50; j++)
        words[i][j] = '\0';

    p = fgets(current_line, 1000, input);
    if (*p)
      while (*p != '\0')
      {
        if (*p == ' ')
        {
          if (flag)
          {
            num_w++;
            pos = 0;
          }
          flag = 0;
        }
        else
          flag = 1;

        words[num_w][pos++] = *p;
        p++;
      }
    flag = 0;

    for (size_t i = 0; i < words[i][0] != '\0'; i++)
      if (i == 2 && !strcmp(words[0], "extern"))
        for (size_t j = 0; words[i][j] != '\0'; j++)
        {
          if (words[i][j] != ';')
            SetConsoleTextAttribute(hStdout, 4);
          printf("%c", words[i][j]);
          SetConsoleTextAttribute(hStdout, 7);
        }
      else
        printf("%s", words[i]);

    num_w = 0;
    pos = 0;
  }
  scanf("%d", &num_w);
  fclose(input);
  return 0;
}