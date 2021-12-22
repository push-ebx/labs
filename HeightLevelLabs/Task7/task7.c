#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_LINE 1000
#define MAX_COUNT_LINE 1000

int main(){
  FILE *input;
  FILE *output;
  input = fopen("input.txt", "r+");
  output = fopen("output.txt", "wt");

  char line[MAX_LEN_LINE];
  char lines[MAX_LEN_LINE][MAX_LEN_LINE];
  int counter = 0;
  int count_line = 0;

  while (!feof(input)){
    fgets(line, MAX_LEN_LINE, input);
    strcpy(lines[counter++], line);
  }

  for (int i = 0; i < counter; i += 2)
  {
    if (i + 2 < counter)
      fputs(lines[i + 1], output);
    if (i + 1 < counter)  
      fputs(lines[i], output);
  }

  fclose(input);
  fclose(output);
  return 0;
}