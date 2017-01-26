/*
** main.c for main in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:47:37 2017
** Last update	Thu Jan 26 12:34:38 2017 Full Name
*/

#include	<unistd.h>
#include	<stdio.h>
#include  "malloc.h"

#define   PAGESIZE sysconf(_SC_PAGESIZE)

static    t_free      *freeStruct;
static    t_malloc    *mallocStruct;

void	check_double_empty()
{
  t_free	*tmp;
  t_free	*tmp2;

  tmp = freeStruct;
  tmp2 = freeStruct;
  while (tmp2)
    {
      freeStruct = tmp;
      while (freeStruct->next != NULL)
	{
	  if (&freeStruct->next == (&freeStruct + freeStruct->size))
	    {
	      freeStruct->size += freeStruct->next->size;
	      if (freeStruct->next->next != NULL)
		freeStruct->next = freeStruct->next->next;
	      else
		freeStruct->next = NULL;
	    }
	  freeStruct = freeStruct->next;
	}
      tmp2 = tmp2->next;
    }
}

void    my_free(void *ptr)
{
  check_double_empty();
}

void		*check_in_free_list(unsigned int size)
{
  t_free	*tmp; 
  while (freeStruct)
    {
      if (freeStruct->size >= size)
	{
	  tmp = freeStruct
	  return(tmp);
	}
      freeStruct = freeStruct->next;
    }
  return (NULL);
}

void		my_malloc(unsigned int size)
{
  static int   mallocStructSize = 0;
  static int   pagerUsedSize = 0;
  // TODO -> check_in_free_list(unsigned int size);
  // si pas de place dans la liste de free -> check si la taille dans le pager est suffisante
  if (check_in_free_list(size) == 1)
    {
    }
  else
    {
      if ((PAGESIZE - pagerUsedSize) < size)
	void  *ptr = sbrk(PAGESIZE);
      else
	{
	}
    }
  /* mallocStruct =  ptr;
  mallocStructSize += sizeof(t_malloc);
  printf("%d\n", mallocStructSize); */
}


int main()
{
  my_malloc(2);
}
