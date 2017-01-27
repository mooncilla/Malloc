/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Fri Jan 27 19:45:16 2017 Full Name
*/

#include  "malloc.h"

#define   PAGESIZE sysconf(_SC_PAGESIZE)

static    t_malloc    *mallocStruct = NULL;
static    size_t      currentPageSize;

void    *check_in_free_list(size_t size)
{
  t_malloc *tmp = mallocStruct;

  while (tmp)
  {
    if (tmp->isFree && tmp->size >= size)
    {
      tmp->isFree = false;
      void *ptrTmp = (void *) tmp  + sizeof(t_malloc) + 1;
      return (ptrTmp);
    }
    tmp = tmp->next;
  }
  return (NULL);
}

void    *push_back_malloc_list(size_t size)
{
    if (mallocStruct == NULL)
    {
      my_putstr("Creation de la liste\n");
      mallocStruct = sbrk(0) - currentPageSize;
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      void *ptr = (void *) mallocStruct + sizeof(t_malloc) + 1;
      return (ptr);
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
      void *ptr = (void *) tmp->next + sizeof(t_malloc) + 1;
      return (ptr);
    }
}

size_t		allow_right(size_t	needed)
{
  size_t	right;

  right = PAGESIZE;
  while (right <= needed)
    right += PAGESIZE;
  return(right);
}

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize;

  if (mallocStruct == NULL)
  {
    pagerUsedSize = allow_right(size);
    currentPageSize = allow_right(size);
  }
  void *ptrTestFree;
  if ((ptrTestFree = check_in_free_list(size)) != NULL)
    return (ptrTestFree);
  if ((currentPageSize - pagerUsedSize) < size)
  {
    my_putstr("New page\n");
    currentPageSize = allow_right(size);
	  sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc)) - (currentPageSize - pagerUsedSize);
    return (push_back_malloc_list(size));
  }
  else
  {
    my_putstr("Existing page\n");
    pagerUsedSize += size + sizeof(t_malloc);
    my_putnbr(pagerUsedSize);
    my_putstr("\n");
    return (push_back_malloc_list(size));
  }
}

void		free(void *ptr)
{
  t_malloc *tmp = mallocStruct;

  while (tmp)
  {
    void *ptrTmp = (void *) tmp  + sizeof(t_malloc) + 1;
    if (ptr == ptrTmp)
    {
      tmp->isFree = true;
      char *value = ptrTmp;
      *value = 0;
      return;
    }
    tmp = tmp->next;
  }
}
