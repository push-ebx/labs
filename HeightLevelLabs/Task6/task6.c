#include <stdio.h> 
#include <stdlib.h>

#define MAX_WORD 100

int getLength(char word[MAX_WORD]);

int main(){
  FILE *f;
  char word[MAX_WORD];
  int count_words = 0;
  int counter = 0;
  int len_word;
  int count_col;

  printf("Enter the number of columns: ");
  scanf("%d", &count_col);

  f = fopen("input.txt", "r");

  while(!feof(f)){ // считаем колво строк
    fscanf(f, "%s", word);
    count_words++;
  }

  int *width_cols = malloc(sizeof(int) * (count_col)); // ширина столбцв

  for (size_t i = 0; i < count_col; i++)
    width_cols[i] = 0;

  fseek(f, 0, 0);

  while(!feof(f)){
    fscanf(f, "%s", word);
    len_word = getLength(word);
    if (width_cols[counter % count_col] < len_word)
      width_cols[counter % count_col] = len_word;
    counter++;
  }

  fseek(f, 0, 0);
  counter = 0;

  while(!feof(f)){
    fscanf(f, "%s", word);
    printf("%s", word);

    for (int i = getLength(word); i < width_cols[counter % count_col] + 2; i++)
      printf(" ");

    counter++;
    if (counter % count_col == 0)
      printf("\n");
  }

  free(width_cols);
  fclose(f);

  printf("\n");
  return 0;
}

int getLength(char word[MAX_WORD]){
  int count = 0;
  while(word[count] != '\0')
    count++;

  return count;
}