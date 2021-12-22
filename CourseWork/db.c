#include <mysql/my_global.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HOST "localhost"
#define PASSWORD ""
#define USER "root"
#define DATABASE "Products"
#define MAX_LEN 100

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
  MYSQL *con = mysql_init(NULL); // сессия подключения
  if (con == NULL)
  {
    printf("error");
    exit(1);
  }
  if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) // подключение
    printf("error");

  rendering_UI(con);
  mysql_close(con);
  exit(0);
}

void concat(char *query[], char result[MAX_LEN], int size)
{
  result[0] = '\0';
  for (int i = 0; i < size; i++)
  {
    strncat(result, query[i], MAX_LEN);
  }
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

void rendering_UI(MYSQL *con)
{
  char command[MAX_LEN];
  char title[MAX_LEN];
  char category[MAX_LEN];
  char price[MAX_LEN];

  print_commands();
  while (1)
  {
    scanf("%s", command);
    print_commands();
    if (!strcmp(command, "Add product") || !strcmp(command, "1"))
    {
      printf("Enter title product>> ");
      scanf("%s", title);
      printf("Enter category product>> ");
      scanf("%s", category);
      printf("Enter price product>> ");
      scanf("%s", price);
      add_product(con, title, category, price);
    }
    else if (!strcmp(command, "Edit product") || !strcmp(command, "2"))
    {
      printf("Select a product to edit>> ");
      scanf("%s", title);
      edit_database(con, title);
    }
    else if (!strcmp(command, "Deleted product") || !strcmp(command, "3"))
    {
      printf("Enter product name to remove>> ");
      scanf("%s", title);
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

      for (int i = 0; i < count; i++)
      {
        printf("Enter the category product's>> ");
        scanf("%s", basket[i]);
      }

      selection_minimum_basket(con, basket, count);
    }
    else
    {
      printf("Undefined command");
    }
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
    {
      printf("error");
    }
    else
    {
      MYSQL_RES *result_sql = mysql_store_result(con);
      if (result_sql == NULL)
        printf("error");
      row = mysql_fetch_row(result_sql);
      printf("%s\n", row[0]);
    }
  }
}

void deleted_product(MYSQL *con, char title[])
{
  char *query[] = {"DELETE from products WHERE title='", title, "';"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));
  if (mysql_query(con, result))
  {
    printf("error");
  }
  else
    printf("Product removed successfully!\n");
}

void edit_database(MYSQL *con, char title[])
{
  char new_title[MAX_LEN];
  char new_category[MAX_LEN];
  char new_price[MAX_LEN];
  printf("Enter a new title product>> ");
  scanf("%s", new_title);
  printf("Enter a new category product>> ");
  scanf("%s", new_category);
  printf("Enter a new price product>> ");
  scanf("%s", new_price);
  char *query[] = {"UPDATE products SET Title='", new_title,
                   "',Category='", new_category, "',Price='",
                   new_price, "' WHERE Title='", title, "';"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));
  
  if (mysql_query(con, result))
    printf("error");
  else
    printf("Product edited successfully!\n");
}

void add_product(MYSQL *con, char title[], char category[], char price[])
{
  char *query[] = {"INSERT products(Title, Category, Price) VALUES ('", title, "','", category, "','", price, "');"};
  char result[MAX_LEN];
  result[0] = '\0';
  concat(query, result, sizeof(query) / sizeof(query[0]));

  if (mysql_query(con, result))
    printf("error");
  else
    printf("Product added successfully!\n");
}

void show_database(MYSQL *con)
{
  if (mysql_query(con, "SELECT * FROM products ORDER BY Category"))
    printf("error");
  else
  {
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
      printf("error");

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    printf("%-20s%-20s%-20s\n\n", "Title", "Category", "Price");
    while ((row = mysql_fetch_row(result)))
    {
      for (int i = 0; i < num_fields; i++)
        printf("%-20s ", row[i] ? row[i] : "NULL");
      printf("\n");
    }
    mysql_free_result(result);
  }
}