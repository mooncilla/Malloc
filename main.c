/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Sat Jan 28 21:12:25 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{

 for (int i = 0; i < 1000; ++i)
  {
    char *test = malloc(4096);
    test = strcpy(test, "test");
    my_putstr("\n");

    char *bonsoir = malloc(4096);
    bonsoir = strcpy(bonsoir, "bonsoir");
//    my_putstr("\n");

    char *oui = malloc(4096);
    oui = strcpy(oui, "oui");
    realloc(oui, 20000);

    my_putnbr(i + 1);
  }

//show_alloc_mem();
//printf("%s\n%s\n%s\n", test, bonsoir, oui); */
}
