/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Fri Jan 27 15:52:21 2017 Full Name
*/

#include <string.h>
#include "malloc.h"

int main()
{
  char *test = malloc(5000);
  //printpointer(test);
  test = strcpy(test, "test");

  char *bonsoir = malloc(3000);
  //printpointer(bonsoir);
  bonsoir = strcpy(bonsoir, "bonsoir");

  char *oui = malloc(200000);
  //printpointer(oui);
  oui = strcpy(oui, "oui");

  //printpointer(sbrk(0));

 printf("%s\n%s\n%s\n", test, bonsoir, oui);
/*  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  } */
}
