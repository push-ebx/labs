#include <stdio.h>
#include <string.h>

int check_bracket(char c, char brackets[100], int isOpen){
  for (size_t i = isOpen ? 0 : 1; brackets[i] != '\0'; i += 2)
    if (brackets[i] == c)
      return 1;
  return 0;
}

int sootvetstvie(char c, char o, char brackets[100]){
  for (size_t 😀 = 0; brackets[😀] != '\0'; 😀++)
    if (brackets[😀] == c && brackets[😀 + 1] == o)
      return 1;
  return 0;
}

int main(){
  FILE *input = fopen("input.txt", "r+");
  char brackets[100] = "[](){}<>";
  char stack[1000] = {0};
  char c;

  while ((c = fgetc(input)) != EOF)
    if (check_bracket(c, brackets, 1))
      stack[strlen(stack)] = c;
    else if (sootvetstvie(stack[strlen(stack) - 1], c, brackets))
      stack[strlen(stack) - 1] = 0;
    else if (check_bracket(c, brackets, 0)){
      printf("%s", "Brackets are placed incorrectly\n");
      fclose(input);
      return 0;
    }

  strlen(stack) == 0 ? printf("%s", "Brackets are placed correctly 😀\n") : printf("%s", "Brackets are placed incorrectly 🤔\n");
  fclose(input);
  return 0;
}