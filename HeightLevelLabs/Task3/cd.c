#include <stdio.h>

int num_input(char[]);
int get_length_str(char[]);

int main()
{
  printf("%d", num_input("aao"));
  return 0;
}

int get_length_str(char len[])
{
  int length = 0;
  while (len[length] != '\0')
    length++;
  return length;
}

int num_input(char str[])
{
  int count = 0;
  char c;
  int pos = 0;

  while ((c = getchar()) != '\n')
  {
    if (c == str[pos])
    {
      pos++;
      if (pos == get_length_str(str))
      {
        count++;
        pos = 0;
      }
    }
    else
      pos = 0;
  }
  return count;
}