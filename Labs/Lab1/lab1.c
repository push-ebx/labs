#include <stdio.h>
#define TRUE 1
#define FALSE 0

int CheckElementInArray(char[], int, char);

int main()
{
  //В символьной строке удалить все слова, содержащие две подряд идущие гласные
  char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
  char line[1000];

  gets(line);

  char c;                // текущий символ
  int prev_c = ' ';      // предыдущий символ
  int is_word = FALSE;   // признак слова
  int found = FALSE;     // признак на удаление
  char *in_ptr = line;   // указатель на входную строку
  char *out_ptr = line;  // указатель на выходную строку
  char *word_ptr = line; // указатель на начало слова

  do
  {
    c = *in_ptr;
    if (c == ' ' || c == '.' || c == ',')
    {
      if (is_word) // символ-разделитель после слова
      {
        if (!found)
          while (word_ptr < in_ptr)
            *out_ptr++ = *word_ptr++; // записываем слово в исходящую строку
        found = FALSE;                // обнуляем признак для удаления строки
        is_word = FALSE;
        *out_ptr++ = c; // запись символа в результирующую строку
      }
    }
    else
    {
      if (!is_word)        // если до этого был символ-разделитель
        word_ptr = in_ptr; //указываем на начало текущего слова
      if (CheckElementInArray(vowels, 6, c) && CheckElementInArray(vowels, 6, prev_c))
        found = TRUE; // найден признак для удаления - 2 гласные подряд
      is_word = TRUE; // признак того, что "мы находимся в слове"
    }
    prev_c = c;
    in_ptr++; // переводим указатель входящей строки на следующий элемент
  } while (c != '\n');
  *out_ptr = '\0';

  puts(line);
  scanf("%c", &c);
  return 0;
}

int CheckElementInArray(char arr[], int len, char c)
{
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == c)
      return 1;
  }
  return 0;
}