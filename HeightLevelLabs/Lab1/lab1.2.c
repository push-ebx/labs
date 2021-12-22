#include <stdio.h>
#include <string.h>

int main(){
  char *footballers[][4] = {
    {
      "Nikita",
      "Smirnov",
      "Alexeyevich",
      "123"
    },
    {
      "Vasiliy", 
      "Ivanov", 
      "Olegovich",
      "103"
    },
    {
      "Artem", 
      "Dziuba", 
      "Sergeevich",
      "223"
    }
  };

  char surname[30];
  char goals[30];
  
  printf("Enter surname: ");
  scanf("%s", surname);

  printf("Enter goals: ");
  scanf("%s", goals);
  printf("\n");
  
  for (size_t i = 0; i < sizeof(footballers) / sizeof(footballers[0]); i++)
  {
    if (!strcmp(footballers[i][1], surname))
    {
      footballers[i][3] = goals;
      printf("Name: %s\nLast Name: %s\nPatronymic: %s\nGoals: %s\n",
      footballers[i][0], footballers[i][1],
      footballers[i][2],footballers[i][3]);
      return 0;
    }
  }
  printf("A player with this surname has not been found!");
  return 0;
}