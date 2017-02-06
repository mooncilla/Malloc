/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Sat Feb 04 22:00:22 2017 Full Name
*/

#include  "malloc.h"

extern    t_malloc    *mallocStruct;
extern    t_free      *freeStruct;

void		show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = mallocStruct;
  my_putstr("break : ");
  printpointer(sbrk(0));
  my_putstr("\n");
  while (tmp)
  {
      void *ptrTmp = (void *) tmp  + sizeof(t_malloc);
      printpointer((void*) tmp);
      my_putstr(" - ");
      printpointer(ptrTmp + tmp->size);
      my_putstr(" : ");
      my_putnbr(tmp->size);
      my_putstr(" bytes\n");
    tmp = tmp->next;
  }
}

t_malloc *getNextMalloc(t_free *tmpToMalloc)
{
  t_malloc *ptr;

  ptr = (void *) tmpToMalloc + tmpToMalloc->size + sizeof(t_malloc);
  while (ptr->c != MALLOC_FLAG)
    ptr = (void *) ptr + ptr->size + sizeof(t_malloc);
  return (ptr);
}

void    *push_back_malloc_list(size_t size, size_t currentPageSize)
{
    if (mallocStruct == NULL)
      return (push_if_null(size, currentPageSize));
    else
    {
      t_malloc *tmp;
      tmp = mallocStruct->end;
      if (freeStruct && freeStruct->end > (t_free *) mallocStruct->end)
        tmp->next = (void *) freeStruct->end + freeStruct->end->size
	  + sizeof(t_free);
      else
        tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      mallocStruct->end = tmp->next;
      tmp->next->size = size;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
      tmp->next->c = MALLOC_FLAG;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      return (ptr);
    }
}

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize;
  static size_t      currentPageSize;

  (size == 0 ? size = 8 : size);
  if (mallocStruct == NULL)
  {
    pagerUsedSize = allow_right(size);
    currentPageSize = allow_right(size);
  }
  void * ptrTestFree;
  if ((ptrTestFree = check_in_free_list(size)) != NULL)
    return (ptrTestFree);
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

void    *realloc(void *ptr, size_t size)
{
  void      *tmp;
  t_malloc  *ptrStruct;

  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  if ((tmp = check_in_free_list(size)) == NULL)
    tmp = malloc(size);
  ptrStruct = ptr - sizeof(t_malloc);
  if (ptrStruct->size < size)
    tmp = memcpy(tmp, ptr, ptrStruct->size);
  else
    tmp = memcpy(tmp, ptr, size);
  free(ptr);
  return (tmp);
}
