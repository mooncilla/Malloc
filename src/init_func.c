/*
** push_back_fct.c for malloc in /home/julian_r/rendu/systeme_unix/PSU_2016_malloc
**
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
**
** Started on  Mon Feb  6 11:58:49 2017 Juliani Renaud
** Last update	Fri Feb 10 23:53:56 2017 Full Name
*/

#include        "malloc.h"

extern t_core   *coreStruct;
extern pthread_mutex_t mutex_malloc;

void		init_mutex()
{
  static int	init = 0;

  if (init == 0)
  {
    mutex_malloc = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    init = 1;
  }
}

void		*init_malloc_head(size_t size, size_t currentPageSize)
{
  if (coreStruct->fList)
    coreStruct->mList = (void *) coreStruct->fEnd
      + coreStruct->fEnd->size + sizeof(t_free);
  else
    coreStruct->mList = sbrk(0) - (currentPageSize - sizeof(t_core));
  coreStruct->mList->size = size;
  coreStruct->mEnd = coreStruct->mList;
  coreStruct->mList->next = NULL;
  coreStruct->mList->prev = NULL;
  coreStruct->mList->flag = MALLOC_FLAG;
  pthread_mutex_unlock(&mutex_malloc);
  return ((void *) coreStruct->mList + sizeof(t_malloc));
}

int       get_multiple(int nb)
{
  int value;

  value = nb % ALIGN;
  if (value == 0)
    return nb;
  return (nb + ALIGN - value);
}

size_t		allow_right(size_t      needed)
{
  return (((needed / PAGESIZE) + 1) * PAGESIZE);
}
