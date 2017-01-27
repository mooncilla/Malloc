/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Fri Jan 27 19:23:49 2017 Full Name
*/

#include <string.h>
#include "malloc.h"

int main()
{
  char *test = malloc(5);
  test = strcpy(test, "test");

  char *bonsoir = malloc(30);
  bonsoir = strcpy(bonsoir, "bonsoir");

  char *oui = malloc(4);
  oui = strcpy(oui, "oui");

 free(bonsoir);

 char *testFree = malloc(20);
 testFree = strcpy(testFree, "testFree");

 printf("%s\n%s\n%s\n", test, bonsoir, oui);
 printf("%s\n", testFree);
/*  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  } */
}
