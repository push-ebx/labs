#include <stdio.h>
#define MAXLINE 1000
void process_line(char buffer[]);
int main(void)
{
  char line[MAXLINE];
  gets(line);
  process_line(line);
  puts(line);
  scanf("%s",line);
  return 0;
}
void process_line(char buffer[])
{
  char c;       // текущий символ
  char *in_ptr; // указатель на текущий символ
  // входной строки
  char *out_ptr; // указатель на текущий символ
  // выходной строки
  char *word_ptr; // указатель на начало слова
  // начальные присваивания (инициализация)
  word_ptr = buffer;
  in_ptr = buffer;
  out_ptr = buffer;
  do
  {
    c = *in_ptr; // взять текущий символ из буфера
    if (c >= '0' && c <= '9')
    {
      in_ptr++;
    }
    else
    {
      *out_ptr++ = *in_ptr;
      in_ptr++;
    }
  } while (c != '\0');
}