/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Mon Jan 30 15:52:48 2017 Full Name
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
      printpointer((void*) tmp);
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
      mallocStruct = sbrk(0) - currentPageSize;
      mallocStruct->size = size;
      mallocStruct->next = NULL;
      mallocStruct->isFree = false;
      //my_putstr("CURRENT : ");
      //printpointer(mallocStruct);
      //my_putstr("\n");
      void *ptr = (void *) mallocStruct + sizeof(t_malloc);
      return (ptr);
    }
    else
    {
      t_malloc *tmp = mallocStruct;
      while (tmp->next)
      {
        //my_putstr("CURRENT :  ");
        //printpointer(tmp);
        //my_putstr(" size -> ");
        ////my_putnbr(tmp->size);
        //my_putstr("    ");
        //(tmp->isFree ?  //my_putnbr(tmp->isFree) : 0);
        //my_putstr("\n");
        tmp = tmp->next;
      }
      tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      tmp->next->size = size;
      tmp->next->isFree = false;
      tmp->next->next = NULL;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      //my_putstr("NEXT : ");
      //printpointer(tmp->next);
      //my_putstr("\n");
      //show_alloc_mem();
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

void   *calloc(size_t nmemb, size_t size)
{
  void *ptr = malloc(nmemb * size);
  ptr = memset(ptr, 0, nmemb * size);
  return (ptr);
}

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize;

  //my_putstr("malloc : ");
    //my_putnbr(size);
  //my_putstr("\n");
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
	  sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc)) - (currentPageSize - pagerUsedSize);
    //my_putstr("pagerUsedSize -> ");
    //my_putnbr(pagerUsedSize);
    //my_putstr("   currentPageSize -> ");
    //my_putnbr(currentPageSize);
    //my_putstr("\n");
    currentPageSize = allow_right(size);
    return (push_back_malloc_list(size));
  }
  else
  {
    pagerUsedSize += size + sizeof(t_malloc);
    //my_putstr("pagerUsedSize -> ");
    //my_putnbr(pagerUsedSize);
    //my_putstr("   currentPageSize -> ");
    //my_putnbr(currentPageSize);
    //my_putstr("\n");
    return (push_back_malloc_list(size));
  }
}

void		free(void *ptr)
{
  t_malloc *tmp;

  if (ptr == NULL)
    return;
  //my_putstr("free : ");
  //printpointer(ptr);
  //my_putstr("\n");
  tmp = mallocStruct;
  void *ptrTmp;
  while (tmp)
  {
    ptrTmp = (void *) tmp  + sizeof(t_malloc);
    if (ptr == ptrTmp)
    {
      tmp->isFree = true;
        //my_putnbr(tmp->size);
      //my_putstr("\n");
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

  //my_putstr("realloc : ");
    //my_putnbr(size);
  //my_putstr("\n");
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
