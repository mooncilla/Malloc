/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Sat Feb 04 03:03:16 2017 Full Name
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
  t_malloc *tmp;

  tmp = mallocStruct->end;
  if (tmp->prev < (t_malloc *) tmpToMalloc)
    return (tmp);
  while (tmp > (t_malloc *) tmpToMalloc)
  {
    if (tmp->prev == NULL)
      return (tmp);
    tmp = tmp->prev;
  }
  return (tmp->next);
}

void    *push_back_malloc_list(size_t size, size_t currentPageSize)
{

    if (mallocStruct == NULL)
    {
      if (freeStruct)
        mallocStruct = (void *) freeStruct->end + freeStruct->end->size + sizeof(t_free);
      else
        mallocStruct = sbrk(0) - currentPageSize;
      mallocStruct->size = size;
      mallocStruct->end = mallocStruct;
      mallocStruct->next = NULL;
      mallocStruct->prev = NULL;
      void *ptr = (void *) mallocStruct + sizeof(t_malloc);
      //pthread_mutex_unlock(&lock_mutex);
      return (ptr);
    }
    else
    {
      t_malloc *tmp;
      tmp = mallocStruct->end;
      if (freeStruct && freeStruct->end > (t_free *) mallocStruct->end)
        tmp->next = (void *) freeStruct->end + freeStruct->end->size + sizeof(t_free);
      else
        tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      mallocStruct->end = tmp->next;
      tmp->next->size = size;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      //pthread_mutex_unlock(&lock_mutex);
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
/*  my_putstr("calloc : ");
  my_putnbr(size);
  my_putstr("\n"); */
  void *ptr = malloc(nmemb * size);
  ptr = memset(ptr, 0, nmemb * size);
  return (ptr);
}

void    lock_mutex_init()
{
    static int init = 0;

    if (init == 0)
    {
      lock_mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
      init = 1;
    }
}

void		*malloc(size_t size)
{
  static size_t   pagerUsedSize;
  static size_t      currentPageSize;

  lock_mutex_init();
  //pthread_mutex_lock(&lock_mutex);
/*  my_putstr("malloc : ");
  my_putnbr(size);
  my_putstr("\n"); */
  (size == 0 ? size = 8 : size);
  if (mallocStruct == NULL)
  {
    pagerUsedSize = allow_right(size);
    currentPageSize = allow_right(size);
  }
  void * ptrTestFree;
  if ((ptrTestFree = check_in_free_list(size)) != NULL)
  {
    //pthread_mutex_unlock(&lock_mutex);
    return (ptrTestFree);
  }
  if ((currentPageSize - pagerUsedSize) < (size + sizeof(t_malloc)))
  {
	  sbrk(allow_right(size));
    pagerUsedSize = (size + sizeof(t_malloc)) - (currentPageSize - pagerUsedSize);
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

  /*my_putstr("realloc : ");
  my_putnbr(size);
  my_putstr("\n");*/
  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  //pthread_mutex_lock(&lock_mutex);
  if ((tmp = check_in_free_list(size)) == NULL)
  {
  //  //pthread_mutex_unlock(&lock_mutex);
    tmp = malloc(size);
  }
  ptrStruct = ptr - sizeof(t_malloc);
  if (ptrStruct->size < size)
    tmp = memcpy(tmp, ptr, ptrStruct->size);
  else
    tmp = memcpy(tmp, ptr, size);
  free(ptr);
  ////pthread_mutex_unlock(&lock_mutex);

  return (tmp);
}
