/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Sat Jan 28 14:55:09 2017 Full Name
*/

#include <string.h>
#include "malloc.h"
#include <stdio.h>

int main()
{
  char *test = malloc(4096);
  test = strcpy(test, "test");

  char *bonsoir = malloc(4096);
  bonsoir = strcpy(bonsoir, "bonsoir");

  char *oui = malloc(4096);
  oui = strcpy(oui, "oui");

  for (int i = 0; i < 2000; ++i)
  {
    char *test = malloc(400);
    test = strcpy(test, "test");
    my_putstr("\n");

    char *bonsoir = malloc(1000);
    bonsoir = strcpy(bonsoir, "bonsoir");
    my_putstr("\n");

    char *oui = malloc(800);
    oui = strcpy(oui, "oui");
    my_putstr("\n");

  }

//  printf("%s\n%s\n%s\n", test, bonsoir, oui);
  free(test);
  free(bonsoir);
  free(oui);
/* printpointer(test);
 printpointer(bonsoir); */

/*  char *testFree = malloc(20);
 testFree = strcpy(testFree, "testFree"); */

 //printf("%s\n", testFree);
/*  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  } */
}
