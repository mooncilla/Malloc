/*
** malloc.c for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Fri Jan 27 12:45:07 2017
** Last update	Fri Feb 03 15:39:33 2017 Full Name
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

t_malloc *getNextMalloc(t_free *tmpToMalloc)
{
  t_malloc *tmp;

  tmp = mallocStruct;
  while (tmp && tmp < (t_malloc*) tmpToMalloc)
  {
    tmp = tmp->next;
/*    my_putstr("SEGSEGDSEG : \n");
    printpointer(tmp);
    my_putstr("\n");
    printpointer(tmpToMalloc);
    my_putstr("\n");
    printpointer(mallocStruct->end);
    my_putstr("\nSEGSEGDSEG : \n"); */
  }
  return (tmp);
}

void    *check_in_free_list(size_t size)
{
  t_free  *tmp;

  tmp = freeStruct;
  while (tmp)
  {
  /*  my_putstr("=======================");
    printpointer(tmp->prev);
    my_putstr(" - ");
    my_putnbr(tmp->size);
    my_putstr("=======================\n"); */
    if (tmp->size >= size /* + sizeof(t_free)*/)
    {
      //show_free_list();
      //show_alloc_mem();
      my_putstr("REUTILISATION \n");

      t_free *tmpToMalloc = tmp;

      //show_free_list();
      if (tmpToMalloc->prev)
      {
        my_putstr("FA\n");
        if (tmpToMalloc->next == NULL)
        {
          freeStruct->end = freeStruct->end->prev;
          freeStruct->end->next = NULL;
        }
        else
        {
        /*  my_putstr("BITTTTTTTTTTTTTTTTTTTTTTEEEE : \n");
          printpointer(tmpToMalloc);
          my_putstr(" --  ");
          printpointer(tmpToMalloc->next);
          my_putstr(" \n"); */
            tmpToMalloc->next->prev = tmpToMalloc->prev;
            tmpToMalloc->prev->next = tmpToMalloc->next;
        }
      }
      else if (freeStruct->next == NULL)
      {
        my_putstr("FB\n");

        freeStruct = NULL;
      }
      else
      {
        my_putstr("FC\n");
        freeStruct->next->end = freeStruct->end;
        freeStruct = freeStruct->next;
        freeStruct->prev = NULL;
      }

  //      show_free_list();
    //  show_alloc_mem();
      my_putstr("end of free list \n");
      printpointer(tmpToMalloc);
      my_putstr("\n");
      if (mallocStruct == NULL)
      {
        mallocStruct = (t_malloc *) tmpToMalloc;
        mallocStruct->end = mallocStruct;
        mallocStruct->next = NULL;
        mallocStruct->prev = NULL;
      }
      else
      {
          if (mallocStruct && mallocStruct->end > (t_malloc *) tmpToMalloc)
          {
            t_malloc *ptrNextMalloc;
            printpointer(mallocStruct->end);
            my_putstr("\n");
            ptrNextMalloc = getNextMalloc(tmpToMalloc);
            if (ptrNextMalloc->prev == NULL)
            {
              my_putstr("MA\n");
              my_putstr("BITTTTTTTTTTTTTTTTTTTTTTEEEE : \n");
              ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
              mallocStruct = (t_malloc *) tmpToMalloc;
              mallocStruct->next = ptrNextMalloc;
              mallocStruct->end = ptrNextMalloc->end;
            }
            else
            {
              my_putstr("MB\n");

              tmpToMalloc->prev = (t_free *) ptrNextMalloc->prev;
              tmpToMalloc->next = (t_free *) ptrNextMalloc;
              ptrNextMalloc->prev->next = (t_malloc *) tmpToMalloc;
              ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
              printpointer(tmpToMalloc->prev);
              my_putstr("  -  ");
              printpointer(tmpToMalloc);
              my_putstr("  -  ");
              printpointer(tmpToMalloc->next);
              my_putstr(" \n");

              //my_putstr("ENNDNENNDNNENDN\n");
              //show_free_list();
              //exit (0);
/*              printpointer(freeStruct);
              my_putstr("  -  ");
              printpointer(freeStruct->end);
              my_putstr("  -  ");
              printpointer(freeStruct->end->next); */

            }
          }
          else
          {
            my_putstr("MC\n");

            mallocStruct->end->next = (t_malloc *) tmpToMalloc;
            mallocStruct->end->next->prev = mallocStruct->end;
            mallocStruct->end = (t_malloc *) tmpToMalloc;
            mallocStruct->end->next = NULL;
          }
      }
      //show_free_list();
      //show_alloc_mem();
      my_putstr("end of reuse ");
      printpointer(mallocStruct->end);
      my_putstr("\n");
      void *returnPtr = (void *) tmpToMalloc + sizeof(t_malloc);
      return (returnPtr);
    }
    tmp = tmp->next;
  }
  return (NULL);
}

void    *push_back_malloc_list(size_t size)
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
      return (ptr);
    }
    else
    {
      t_malloc *tmp;
      tmp = mallocStruct->end;
      if (freeStruct && freeStruct->end > (t_free *) mallocStruct->end)
      {
          my_putstr("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
          //void *ma = (void *) freeStruct->end + freeStruct->end->size + sizeof(t_malloc);
          /* printpointer(ma);
          my_putstr("  -  ");
          printpointer((void *) freeStruct->end);
          my_putstr("\n");
          //show_free_list(); */
          tmp->next = (void *) freeStruct->end + freeStruct->end->size + sizeof(t_free);
      }
      else
      {
        tmp->next = (void *) tmp + tmp->size + sizeof(t_malloc);
      }
    //  show_free_list();
      mallocStruct->end = tmp->next;
      tmp->next->size = size;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
      void *ptr = (void *) tmp->next + sizeof(t_malloc);
      my_putstr("===========SORTIE MALLOC===========\n");
      //show_free_list();
  //    show_alloc_mem();
    //  show_free_list();
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
  my_putstr(" : ");
  my_putnbr(nmemb);
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
  my_putstr("===========ENTRE MALLOC===========\n");
//  show_free_list();
  //my_putstr("\n");

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
    if (ptr > freeStruct->end)
    {
      if ((void *) freeStruct->end + freeStruct->end->size + sizeof(t_malloc) == (void *) ptr)
      {
        my_putstr("OUIIIIIIIIIIIIIIIIIIIIII \n");
        freeStruct->end->size += ptr->size + sizeof(t_malloc);
        ptr->prev = NULL;
        ptr->next = NULL;
      }
      else
      {
        freeStruct->end->next = ptr;
        freeStruct->end->next->prev = freeStruct->end;
        freeStruct->end = ptr;
        //  freeStruct->end->size = ptr->size;
        freeStruct->end->next = NULL;
      }
    }
    else
    {
      ptr->end = freeStruct->end;
      ptr->prev = NULL;
      ptr->next = freeStruct;
      freeStruct->prev = ptr;
      freeStruct = ptr;
    }
  }
  //show_alloc_mem();
  //show_free_list();

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
  {
    if (tmp->next == NULL)
    {
      mallocStruct->end = mallocStruct->end->prev;
      mallocStruct->end->next = NULL;
    }
    else
    {
      tmp->next->prev = tmp->prev;
      tmp->prev->next = tmp->next;
    }
  }
  else if (mallocStruct->next == NULL)
    mallocStruct = NULL;
  else
  {
    mallocStruct->next->end = mallocStruct->end;
    mallocStruct = mallocStruct->next;
    mallocStruct->prev = NULL;
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
