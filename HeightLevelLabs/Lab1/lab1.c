#include <stdio.h>
#include <string.h>
// Создать массив игроков (ФИО, число забитых мячей). По фамилии
// изменить число. Вывести на экран.
typedef struct 
{
	char first_name[20];
  char last_name[20];
  char patronymic[20];
  int goals;
} footballer;

int main(){
  footballer footballers[] = {
    "Nikita", "Smirnov", "Alexeyevich", 1234,
    "Vasiliy", "Ivanov", "Olegovich", 103,
    "Artem", "Dziuba", "Sergeevich", 223 };

  char last_name[20];
  int goals;
  
  printf("Enter last name: ");
  scanf("%s", last_name);

  printf("Enter goals: ");
  scanf("%d", &goals);
  printf("\n");

  for (size_t i = 0; i < sizeof(footballers) / sizeof(footballers)[0]; i++)
  {
    if (!strcmp(footballers[i].last_name, last_name))
    {
      footballers[i].goals = goals;
      printf("Name: %s\nLast Name: %s\nPatronymic: %s\nGoals: %d\n",
      footballers[i].first_name, footballers[i].last_name,
      footballers[i].patronymic,footballers[i].goals);
    }
  }
  return 0;
}