/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Sun Jan 29 00:03:34 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *test;
  char *bonsoir;
  char *oui;

 for (int i = 0; i < 1; ++i)
  {
   test = malloc(4096);
    test = strcpy(test, "test");

    bonsoir = malloc(4096);
    bonsoir = strcpy(bonsoir, "bonsoir");
//    my_putstr("\n");

    oui = malloc(4096);
    oui = strcpy(oui, "oui");
    //oui = realloc(oui, 400);

    free(bonsoir);
    my_putnbr(i + 1);
    my_putstr("\n");
  }
  show_alloc_mem();

printpointer(test);
my_putstr("\n");
printpointer(oui);
my_putstr("\n");
my_putstr(test);
my_putstr("\n");
my_putstr(bonsoir);
my_putstr("\n");
my_putstr(oui);
my_putstr("\n");
}
