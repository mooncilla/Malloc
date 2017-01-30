/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Mon Jan 30 14:18:11 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *test;
  char *bonsoir;
  char *oui;

for (int i = 0; i < 1000; ++i)
  {
   test = malloc(5);
    test = strcpy(test, "test");

    bonsoir = malloc(i * 3 + 1);
    bonsoir = strcpy(bonsoir, "bonsoir");
//    my_putstr("\n");

    oui = malloc(i * 8 + 1);
    oui = strcpy(oui, "oui");
    oui = realloc(oui, i * 9 + 1);

    my_putnbr(i + 1);
    my_putstr("\n");
  }

  show_alloc_mem();


  my_putstr(test);
  my_putstr("\n");
  my_putstr(bonsoir);
  my_putstr("\n");
  my_putstr(oui);
  my_putstr("\n");
}
