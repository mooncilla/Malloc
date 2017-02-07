/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Tue Feb 07 15:01:19 2017 Full Name
*/

#include        "malloc.h"

extern t_malloc *mallocStruct;
extern t_free   *freeStruct;
extern pthread_mutex_t mutex_malloc;

void		lock_mutex_init()
{
  static int	init = 0;

  if (init == 0)
  {
    mutex_malloc = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    init = 1;
  }
}

t_malloc	*getNextMalloc(t_free *tmpToMalloc)
{
  t_malloc	*ptr;

  ptr = (void *) tmpToMalloc + tmpToMalloc->size + sizeof(t_malloc);
  while (ptr->flag != MALLOC_FLAG)
    ptr = (void *) ptr + ptr->size + sizeof(t_malloc);
  return (ptr);
}

void		*push_back_malloc_list(size_t size, size_t currentPageSize)
{
    t_malloc	*tmp;

    if (mallocStruct == NULL)
    {
      return (push_if_null(size, currentPageSize));
    }
    else
    {
      tmp = mallocStruct->end;
      if (freeStruct && freeStruct->end > (t_free *) mallocStruct->end)
        tmp->next = (void *) freeStruct->end
        + freeStruct->end->size + sizeof(t_free);
      else
        tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      mallocStruct->end = tmp->next;
      tmp->next->size = size;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
      tmp->next->flag = MALLOC_FLAG;
      pthread_mutex_unlock(&mutex_malloc);
      return ((void *) tmp->next + sizeof(t_malloc));
    }
}

void		*allow_memory(size_t size)
{
  static size_t pagerUsedSize;
  static size_t currentPageSize;

  if (mallocStruct == NULL)
  {
    pagerUsedSize = allow_right(size);
    currentPageSize = allow_right(size);
  }
  if ((currentPageSize - pagerUsedSize) < (size + sizeof(t_malloc)))
  {
    sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc))
    - (currentPageSize - pagerUsedSize);
    currentPageSize = allow_right(size);
    return (push_back_malloc_list(size, currentPageSize));
  }
  else
  {
    pagerUsedSize += size + sizeof(t_malloc);
    return (push_back_malloc_list(size, currentPageSize));
  }
}

void		*malloc(size_t size)
{
  void		*ptrTestFree;

  lock_mutex_init();
  pthread_mutex_lock(&mutex_malloc);
  if (size > (size_t) sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGE_SIZE))
  {
    pthread_mutex_unlock(&mutex_malloc);
    return (NULL);
  }
  (size == 0 ? size = 8 : size);
  if ((ptrTestFree = check_in_free_list(size)) != NULL)
  {
    pthread_mutex_unlock(&mutex_malloc);
    return (ptrTestFree);
  }
  return (allow_memory(size));
}
