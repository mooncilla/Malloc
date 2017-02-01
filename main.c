/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Wed Feb 01 21:47:01 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *test;
  char *bonsoir;
  char *oui;

for (int i = 0; i < 2; ++i)
  {
   test = malloc(1000);
//test = strcpy(test, "test");

//    bonsoir = malloc(500);
  //  bonsoir = strcpy(bonsoir, "bonsoir");
//    my_putstr("\n");
my_putstr("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
//show_alloc_mem();
show_free_list();
    oui = malloc(100);
    oui = strcpy(oui, "oui");
    //oui = realloc(oui, (i + 1) * 10);

    show_alloc_mem();
    //free(test);
    //free(bonsoir);
    free(oui);
    show_alloc_mem();
    show_free_list();
    my_putnbr(i + 1);
    my_putstr("\n");

  }


  my_putstr(test);
  my_putstr("\n");
  my_putstr(bonsoir);
  my_putstr("\n");
  my_putstr(oui);
  my_putstr("\n");
}
