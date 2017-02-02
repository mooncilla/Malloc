/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Thu Feb 02 03:50:05 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *test;
  char *bonsoir;
  char *oui;

for (int i = 0; i < 3; ++i)
  {
   test = malloc(100);
   test = strcpy(test, "test");
   my_putstr(" Test adress :  ");
   printpointer(test - sizeof(t_malloc));
   my_putstr("\n");

    bonsoir = malloc(500);
    bonsoir = strcpy(bonsoir, "bonsoir");
    my_putstr(" Bonsoir adress :  ");
    printpointer(bonsoir - sizeof(t_malloc));
    my_putstr("\n");
//    my_putstr("\n");
//my_putstr("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
//show_alloc_mem();
//show_free_list();
//show_alloc_mem();
    oui = malloc(1000);
    oui = strcpy(oui, "oui");
    my_putstr(" Oui adress :  ");
    printpointer(oui - sizeof(t_malloc));
    my_putstr("\n");
//oui = realloc(oui, (i + 1) * 10);

    show_alloc_mem();
    show_free_list();
    free(test);
    //free(bonsoir);
    free(oui);
    my_putstr(" --------------PRINT OF END------------- \n");
    show_alloc_mem();
    show_free_list();
    my_putnbr(i + 1);
    my_putstr("\n");
    my_putstr(" --------------END OF LOOP------------- \n");

  }


  my_putstr(test);
  my_putstr("\n");
  my_putstr(bonsoir);
  my_putstr("\n");
  my_putstr(oui);
  my_putstr("\n");
}
