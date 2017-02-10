/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Fri Feb 10 23:47:02 2017 Full Name
*/

#include        "malloc.h"

extern t_core *coreStruct;
extern pthread_mutex_t mutex_malloc;

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

    if (coreStruct->mList == NULL)
      return (init_malloc_head(size, currentPageSize));
    else
    {
      tmp = coreStruct->mEnd;
      if (coreStruct->fList && coreStruct->fEnd > (t_free *) coreStruct->mEnd)
        tmp->next = (void *) coreStruct->fEnd
        + coreStruct->fEnd->size + sizeof(t_free);
      else
        tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      coreStruct->mEnd = tmp->next;
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

  if (coreStruct == NULL)
  {
    coreStruct = sbrk(allow_right(size + sizeof(t_core)));
    currentPageSize = allow_right(size + sizeof(t_core));
    pagerUsedSize = size + sizeof(t_malloc) + sizeof(t_core);
    return (push_back_malloc_list(size, currentPageSize));
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

  init_mutex();
  pthread_mutex_lock(&mutex_malloc);
  size = get_multiple(size);
  if (size > (size_t) sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGE_SIZE))
  {
    pthread_mutex_unlock(&mutex_malloc);
    return (NULL);
  }
  if (coreStruct && (ptrTestFree = check_in_free_list(size)) != NULL)
  {
    pthread_mutex_unlock(&mutex_malloc);
    return (ptrTestFree);
  }
  return (allow_memory(size));
}
