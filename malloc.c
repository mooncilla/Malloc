/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Fri Jan 27 13:36:51 2017 Full Name
*/

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

int		check_in_free_list(size_t size)
{
/*  while (freeStruct)
    {
      if (freeStruct->size >= size)
	return(1);
      freeStruct = freeStruct->next;
  } */
  return (0);
}

void    *push_back_malloc_list(size_t size)
{
    if (mallocStruct == NULL)
    {
      //my_putstr("Creation de la liste\n");
      mallocStruct = sbrk(0) - 4096;
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      return (mallocStruct + sizeof(t_malloc) + 1);
    }
    else
    {
      //my_putstr("Nouveau maillon\n");
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

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize = 4096;
  // TODO -> check_in_free_list(size_t size);
  // si pas de place dans la liste de free -> check si la taille dans le pager est suffisante
/*  if (check_in_free_list(size) == 1)
    {
    }
  else
    { */
      if ((PAGESIZE - pagerUsedSize) < size)
      {
        //my_putstr("New page\n");
	      sbrk(PAGESIZE);
        pagerUsedSize = (size + sizeof(t_malloc)) - (PAGESIZE - pagerUsedSize);
        return (push_back_malloc_list(size));
      }
      else
      {
        //my_putstr("Existing page\n");
        pagerUsedSize += size + sizeof(t_malloc);
        return (push_back_malloc_list(size));
      }
}

void		free()
{

}
