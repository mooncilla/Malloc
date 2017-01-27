/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Fri Jan 27 09:55:22 2017 Full Name
*/

#include	<unistd.h>
#include	<stdio.h>
#include  "malloc.h"

#define   PAGESIZE sysconf(_SC_PAGESIZE)

static    t_malloc    *mallocStruct = NULL;

void	check_double_empty()
{
  /* t_free	;
  while (freeStruct && freeStruct->next != NULL)
    {
      if (&freeStruct == (&freeStruct + )
    } */
}

void    my_free(void *ptr)
{
  check_double_empty();
}

int		check_in_free_list(unsigned int size)
{
/*  while (freeStruct)
    {
      if (freeStruct->size >= size)
	return(1);
      freeStruct = freeStruct->next;
  } */
  return (0);
}

void    *push_back_malloc_list(unsigned int size)
{
    if (mallocStruct == NULL)
    {
      //printf("Creation de la liste\n");
      mallocStruct = sbrk(0) - 4096;
      //printf("ptr = %p\n", mallocStruct);
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      return (mallocStruct + sizeof(t_malloc) + 1);
    }
    else
    {
      void *tmp = mallocStruct;
      while (mallocStruct->next)
        mallocStruct = mallocStruct->next;
    //  //printf("avant= %s\n", mallocStruct + sizeof(t_malloc) + 1);
      //printf("Nouveau maillon\n");
      //printf("%d\n",mallocStruct->size + sizeof(t_malloc) + 1);
      mallocStruct->next = mallocStruct + mallocStruct->size + sizeof(t_malloc) + 1;
      mallocStruct->next->size = size;
      mallocStruct->next->isFree = false;
      mallocStruct->next->next = NULL;
      mallocStruct = tmp;
      return (mallocStruct->next + sizeof(t_malloc) + 1);
    }
}

void		*my_malloc(unsigned int size)
{
  static int   pagerUsedSize = 4096;
  // TODO -> check_in_free_list(unsigned int size);
  // si pas de place dans la liste de free -> check si la taille dans le pager est suffisante
/*  if (check_in_free_list(size) == 1)
    {
    }
  else
    { */
      if ((PAGESIZE - pagerUsedSize) < size)
      {
	       void *ptr = sbrk(PAGESIZE);
         //printf("%p\n", ptr);
         pagerUsedSize = (size + sizeof(t_malloc)) - (PAGESIZE - pagerUsedSize);
         //printf("New page %d\n", pagerUsedSize);
         return (push_back_malloc_list(size));
      }
      else
      {
        pagerUsedSize += size + sizeof(t_malloc);
        //printf("Existing page %d\n", pagerUsedSize);
        return (push_back_malloc_list(size));
      }
}

#include <string.h>

int main()
{
  /*oid *ptr1 = sbrk(10);
   printf("bite\n");
  void *ptr2 = sbrk(0) - 10;
  printf("%p\n", ptr1);
  printf("%p\n", ptr2);
return(0); */
  char *test = my_malloc(500);
  test = strcpy(test, "bite");

  char *bonsoir = my_malloc(200);
  bonsoir = strcpy(bonsoir, "b");

  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  }
}
