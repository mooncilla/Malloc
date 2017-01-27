/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Fri Jan 27 13:41:14 2017 Full Name
*/

#include <string.h>
#include "malloc.h"

int main()
{
  char *test = malloc(5000);
  test = strcpy(test, "test");

  char *bonsoir = malloc(300);
  bonsoir = strcpy(bonsoir, "bonsoir");

  char *oui = malloc(20);
  oui = strcpy(oui, "oui");

printf("%s\n%s\n%s\n", test, bonsoir, oui);
/*  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  } */
}
