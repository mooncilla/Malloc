/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Sun Jan 29 00:05:21 2017 Full Name
*/

#include  "malloc.h"

#define   PAGESIZE sysconf(_SC_PAGESIZE)

static    t_malloc    *mallocStruct = NULL;
static    size_t      currentPageSize;

void		show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = mallocStruct;
  my_putstr("break : ");
  printpointer(sbrk(0));
  my_putstr("\n");
  while (tmp)
  {
    if (!tmp->isFree)
    {
      void *ptrTmp = (void *) tmp  + sizeof(t_malloc);
      printpointer(ptrTmp);
      my_putstr(" - ");
      printpointer(ptrTmp + tmp->size);
      my_putstr(" : ");
      my_putnbr(tmp->size);
      my_putstr(" bytes\n");
    }
    tmp = tmp->next;
  }
}

void    *check_in_free_list(size_t size)
{
  t_malloc *tmp;

  tmp = mallocStruct;
  while (tmp)
  {
    if (tmp->isFree && tmp->size >= size)
    {
      tmp->isFree = false;
      void *ptrTmp = (void *) tmp  + sizeof(t_malloc);
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
      //my_putstr("Creation de la liste\n");
      mallocStruct = sbrk(0) - currentPageSize;
      //printpointer(mallocStruct);
      //my_putstr("\n");
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      void *ptr = (void *) mallocStruct + sizeof(t_malloc);
      return (ptr);
    }
    else
    {
      //my_putstr("Nouveau maillon\n");
      t_malloc *tmp = mallocStruct;
      while (tmp->next)
        tmp = tmp->next;
      tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      //printpointer(tmp->next);
      //my_putstr("\n");
      tmp->next->size = size;
      tmp->next->isFree = false;
      tmp->next->next = NULL;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      return (ptr);
    }
}

size_t		allow_right(size_t	needed)
{
  size_t	right;

  right = PAGESIZE;
  while (right <= (needed + sizeof(t_malloc)))
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
  if ((currentPageSize - pagerUsedSize) < (size + sizeof(t_malloc)))
  {
    //my_putstr("New page\n");
    //my_putstr("Size= ");
    //my_putnbr(size);
    //my_putstr("\n");
    //my_putnbr(pagerUsedSize);
    //my_putstr("\n");
	  sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc)) - (currentPageSize - pagerUsedSize);
    //my_putnbr(pagerUsedSize);
    //my_putstr("\n");
    currentPageSize = allow_right(size);
    //my_putnbr(currentPageSize);
    //my_putstr("\n");
    return (push_back_malloc_list(size));
  }
  else
  {
    //my_putstr("Existing page\n");
    //my_putstr("Size= ");
    //my_putnbr(size);
    //my_putstr("\n");
    //my_putnbr(pagerUsedSize);
    //my_putstr("\n");
    pagerUsedSize += size + sizeof(t_malloc);
    //my_putnbr(pagerUsedSize);
    //my_putstr("\n");
    //my_putnbr(currentPageSize);
    //my_putstr("\n");
    return (push_back_malloc_list(size));
  }
}

void		free(void *ptr)
{
  t_malloc *tmp;

  tmp = mallocStruct;
  void *ptrTmp;
  while (tmp)
  {
    ptrTmp = (void *) tmp  + sizeof(t_malloc);
    if (ptr == ptrTmp)
    {
      tmp->isFree = true;
      memset(ptrTmp, 0, tmp->size);
    /*  char *value = ptrTmp;
      *value = 0; */
      return;
    }
    tmp = tmp->next;
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
  tmp = NULL;
  if ((tmp = check_in_free_list(size)) != NULL)
    return (tmp);
  ptrStruct = ptr - sizeof(t_malloc);
  tmp = malloc(size);
  if (ptrStruct->size < size)
    tmp = memcpy(tmp, ptr, ptrStruct->size);
  else
    tmp = memcpy(tmp, ptr, size);
  free(ptr);
  return (tmp);
}
