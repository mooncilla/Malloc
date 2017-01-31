/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Tue Jan 31 15:33:49 2017 Full Name
*/

#include  "malloc.h"

#define   PAGESIZE sysconf(_SC_PAGESIZE)

static    t_malloc    *mallocStruct = NULL;
static    t_free      *freeStruct = NULL;
static    size_t      currentPageSize;

void    show_free_list()
{
  t_free *tmp;

  tmp = freeStruct;
  my_putstr("freeList : ");
  my_putstr("\n");
  while (tmp)
  {
      void *ptrTmp = (void *) tmp  + sizeof(t_free);
      printpointer((void*) tmp);
      my_putstr(" - ");
      printpointer(ptrTmp + tmp->size);
      my_putstr(" : ");
      my_putnbr(tmp->size);
      my_putstr(" bytes\n");
    tmp = tmp->next;
  }
}

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

void    *check_in_free_list(size_t size)
{
  t_free *tmp;

  tmp = freeStruct;
  while (tmp)
  {
    if (tmp->size >= size)
    {
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
      mallocStruct = sbrk(0) - currentPageSize;
      mallocStruct->size = size;
      mallocStruct->end = mallocStruct;
      mallocStruct->next = NULL;
      mallocStruct->prev = NULL;
      void *ptr = (void *) mallocStruct + sizeof(t_malloc);
      return (ptr);
    }
    else
    {
      t_malloc *tmp;
      tmp = mallocStruct->end;
      tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      mallocStruct->end = tmp->next;
      tmp->next->size = size;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      return (ptr);
    }
}

size_t		allow_right(size_t	needed)
{
  size_t	right;

  right = PAGESIZE * 2;
  while (right <= (needed + sizeof(t_malloc)))
    right += PAGESIZE;
  return(right);
}

void   *calloc(size_t nmemb, size_t size)
{
  my_putstr("calloc : ");
  my_putnbr(size);
  my_putstr("\n");
  void *ptr = malloc(nmemb * size);
  ptr = memset(ptr, 0, nmemb * size);
  return (ptr);
}

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize;

  my_putstr("malloc : ");
  my_putnbr(size);
  my_putstr("\n");
  if (mallocStruct == NULL)
  {
    pagerUsedSize = allow_right(size);
    currentPageSize = allow_right(size);
  }
//  if ((ptrTestFree = check_in_free_list(size)) != NULL)
  //  return (ptrTestFree);
  if ((currentPageSize - pagerUsedSize) < (size + sizeof(t_malloc)))
  {
	  sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc)) - (currentPageSize - pagerUsedSize);
    currentPageSize = allow_right(size);
    return (push_back_malloc_list(size));
  }
  else
  {
    pagerUsedSize += size + sizeof(t_malloc);
    return (push_back_malloc_list(size));
  }
}

void    add_to_free_list(t_free *ptr)
{
  if (freeStruct == NULL)
  {
    freeStruct = ptr;
    freeStruct->end = freeStruct;
    freeStruct->next = NULL;
    freeStruct->prev = NULL;
  }
  else
  {
    my_putstr("AVANT \n");
    printpointer((void *) freeStruct->end + freeStruct->size + sizeof(t_malloc));
    my_putstr("    ");
    printpointer((void *) ptr);
    my_putstr(" \n");
    if ((void *) freeStruct->end + freeStruct->size + sizeof(t_malloc) == (void *) ptr)
    {
      my_putstr("OUIIIII \n");
      freeStruct->end->size += ptr->size + sizeof(t_malloc);
    }
    else
    {
      freeStruct->end->next = ptr;
      freeStruct->end->next->prev = freeStruct->end;
      freeStruct->end = ptr;
      freeStruct->end->size = ptr->size;
      freeStruct->end->next = NULL;
    }
/*    freeStruct->end->next = ptr;
    freeStruct->end->next->prev = freeStruct->end;
    freeStruct->end = ptr;
    freeStruct->end->size = ptr->size;
    freeStruct->end->next = NULL; */
  }
}

void		free(void *ptr)
{
  t_malloc *tmp;

  if (ptr == NULL)
    return;
  my_putstr("free : ");
  printpointer(ptr - sizeof(t_malloc));
  my_putstr("\n");
  tmp = ptr - sizeof(t_malloc);
  if (tmp->prev)
    tmp->prev->next = tmp->next;
  else if (mallocStruct->next == NULL)
    mallocStruct = NULL;
  else
  {
    mallocStruct = mallocStruct->next;
    mallocStruct->prev = NULL;
    if (mallocStruct->end == NULL)
      mallocStruct->end = mallocStruct;
  }
  memset(ptr, 0, tmp->size);
  add_to_free_list((t_free *) tmp);
}

void    *realloc(void *ptr, size_t size)
{
  void      *tmp;
  t_malloc  *ptrStruct;

  my_putstr("realloc : ");
  my_putnbr(size);
  my_putstr("\n");
  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  tmp = NULL;
//  if ((tmp = check_in_free_list(size)) != NULL)
  //  return (tmp);
  ptrStruct = ptr - sizeof(t_malloc);
  tmp = malloc(size);
  if (ptrStruct->size < size)
    tmp = memcpy(tmp, ptr, ptrStruct->size);
  else
    tmp = memcpy(tmp, ptr, size);
  free(ptr);
  return (tmp);
}
