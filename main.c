/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Fri Jan 27 11:17:19 2017 Full Name
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
      my_putstr("Creation de la liste\n");
      mallocStruct = sbrk(0) - 4096;
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      return (mallocStruct + sizeof(t_malloc) + 1);
    }
    else
    {
      my_putstr("Nouveau maillon\n");
      t_malloc *tmp = mallocStruct;
      while (tmp->next)
        tmp = tmp->next;
      tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc) + 1;
      tmp->next->size = size;
      tmp->next->isFree = false;
      tmp->next->next = NULL;
      return (tmp->next + sizeof(t_malloc) + 1);
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
        my_putstr("New page\n");
	       void *ptr = sbrk(PAGESIZE);
         pagerUsedSize = (size + sizeof(t_malloc)) - (PAGESIZE - pagerUsedSize);
         return (push_back_malloc_list(size));
      }
      else
      {
        my_putstr("Existing page\n");
        pagerUsedSize += size + sizeof(t_malloc);
        return (push_back_malloc_list(size));
      }
}

#include <string.h>

int main()
{
  char *test = my_malloc(4080);
  test = strcpy(test, "test");

  char *bonsoir = my_malloc(200);
  bonsoir = strcpy(bonsoir, "bonsoir");

  char *oui = my_malloc(20);
  oui = strcpy(bonsoir, "oui");

  while (mallocStruct)
  {
    printf("data= %s\n", mallocStruct + sizeof(t_malloc) + 1);
    mallocStruct = mallocStruct->next;
  }
}
