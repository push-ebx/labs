#include <mysql/my_global.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>

#define HOST "localhost"    // имя сервера
#define PASSWORD ""         // пароль от бд
#define USER "root"         // имя пользователя бд
#define DATABASE "Products" //название бд
#define MAX_LEN 100         // максимальная длина строки

void concat(char *[], char *, int);
void add_product(MYSQL *, char[], char[], char[]);
void show_database(MYSQL *);
void deleted_product(MYSQL *, char[]);
void rendering_UI(MYSQL *);
void edit_database(MYSQL *con, char title[]);
void selection_minimum_basket(MYSQL *con, char[100][MAX_LEN], int);

// Пополнение базы.
// Редактирование базы.
// Удаление записей.
// Вывод содержимого базы в алфавитном порядке по названию товара, либо по категориям товара.
// Подбор "минимальной корзины" по заданному списку продуктов.

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL); // инициализация сессии
  if (con == NULL)
  {
    printf("error\n");
    exit(1);
  }
  if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) // подключение
    printf("error\n");

  rendering_UI(con);
  mysql_close(con); // закрываем сессию
  exit(0);
}

void concat(char *query[], char result[MAX_LEN], int size)
{
  result[0] = '\0';
  for (int i = 0; i < size; i++)
    strncat(result, query[i], MAX_LEN);
}

void print_commands()
{
  system("clear");
  printf("Select database action...\n");
  printf("1 - Add product\n");
  printf("2 - Edit product\n");
  printf("3 - Deleted product\n");
  printf("4 - Print database\n");
  printf("5 - Selection of the \"minimum basket\"\n\n");
}

void read_line(char str[100])
{
  char c;
  for (int i = 0; i < 100; i++)
    str[i] = '\0';

  int i = 0;
  if ((c = getchar()) != '\n')
  {
    str[i++] = c;
    while ((c = getchar()) != '\n')
      str[i++] = c;
  }
  else
  {
    i++;
    while ((c = getchar()) != '\n')
    {
      str[i - 1] = c;
      i++;
    }
  }
}

void rendering_UI(MYSQL *con)
{
  char command[MAX_LEN];
  char title[MAX_LEN];
  char category[MAX_LEN];
  char price[MAX_LEN];
  int i = 0;
  char c;
  print_commands();
  while (1)
  {
    read_line(command);
    print_commands();
    if (!strcmp(command, "Add product") || !strcmp(command, "1"))
    {
      printf("Enter title product>> ");
      read_line(title);
      printf("Enter category product>> ");
      read_line(category);
      printf("Enter price product>> ");
      read_line(price);
      add_product(con, title, category, price);
    }
    else if (!strcmp(command, "Edit product") || !strcmp(command, "2"))
    {
      printf("Select a product to edit>> ");
      read_line(title);
      edit_database(con, title);
    }
    else if (!strcmp(command, "Deleted product") || !strcmp(command, "3"))
    {
      printf("Enter product name to remove>> ");
      read_line(title);
      deleted_product(con, title);
    }
    else if (!strcmp(command, "Print database") || !strcmp(command, "4"))
    {
      show_database(con);
    }
    else if (!strcmp(command, "Selection of the \"minimum basket\"") || !strcmp(command, "5"))
    {
      char basket[100][MAX_LEN];
      int count = 0;
      printf("Enter the count prodocts in list>> ");
      scanf("%d", &count);

      for (int j = 0; j < count; j++)
      {
        printf("Enter the category product's>> ");
        read_line(basket[j]);
      }
      selection_minimum_basket(con, basket, count);
    }
    else
      printf("Undefined command");
  }
}

void selection_minimum_basket(MYSQL *con, char basket[100][100], int count)
{
  MYSQL_ROW row;
  char result[MAX_LEN];
  for (int i = 0; i < count; i++)
  {
    char *query[] = {"SELECT * FROM products WHERE Category='", basket[i], "' ORDER BY Price;"};
    result[0] = '\0';
    concat(query, result, sizeof(query) / sizeof(query[0]));
    if (mysql_query(con, result))
      printf("error\n");
    else
    {
      MYSQL_RES *result_sql = mysql_store_result(con);
      if (result_sql == NULL)
        printf("error\n");
      row = mysql_fetch_row(result_sql); // ответ от бд
      printf("%s\n", row[0]);
    }
  }
}

void deleted_product(MYSQL *con, char title[])
{
  char *query[] = {"DELETE from products WHERE title=\"", title, "\";"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));
  if (mysql_query(con, result))
    printf("error\n");
  else
    mysql_affected_rows(con) ? printf("Product removed successfully!\n") : printf("Product not found\n"); // проверка на наличие файла
}

void edit_database(MYSQL *con, char title[])
{
  char new_title[MAX_LEN];
  char new_category[MAX_LEN];
  char new_price[MAX_LEN];
  printf("Enter a new title product>> ");
  read_line(new_title);
  printf("Enter a new category product>> ");
  read_line(new_category);
  printf("Enter a new price product>> ");
  read_line(new_price);
  char *query[] = {"UPDATE products SET Title='", new_title,
                   "',Category='", new_category, "',Price='",
                   new_price, "' WHERE Title='", title, "';"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));

  if (mysql_query(con, result))
    printf("error\n");
  else
    mysql_affected_rows(con) ? printf("Product edited successfully!\n") : printf("Error, maybe the product was not found\n");
}

void add_product(MYSQL *con, char title[], char category[], char price[])
{
  char *query[] = {"INSERT products(Title, Category, Price) VALUES ('", title, "','", category, "','", price, "');"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));

  if (mysql_query(con, result))
    printf("error\n");
  else
    printf("Product added successfully!\n");
}

void show_database(MYSQL *con)
{
  if (mysql_query(con, "SELECT * FROM products ORDER BY Category"))
    printf("error\n");
  else
  {
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
      printf("error\n");

    int num_fields = mysql_num_fields(result); // количество колонок в таблице
    MYSQL_ROW row;

    printf("%-20s%-20s%-20s\n\n", "Title", "Category", "Price");
    while ((row = mysql_fetch_row(result)))
    {
      for (int i = 0; i < num_fields; i++)
        printf("%-20s ", row[i] ? row[i] : "NULL");
      printf("\n");
    }
    mysql_free_result(result); // удаляем данные
  }
}