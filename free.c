/*
** free.c for free in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Sat Feb  4 02:37:06 2017
** Last update	Sat Feb 04 03:01:29 2017 Full Name
*/

#include  "malloc.h"

extern    t_malloc    *mallocStruct;
extern    t_free      *freeStruct;

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

t_free *getNextFree(t_free *tmpToMalloc)
{
  t_free *tmp;

  tmp = freeStruct->end;
  if (tmp->prev < tmpToMalloc)
    return (tmp);
  while (tmp > (t_free *) tmpToMalloc)
  {
    if (tmp->prev == NULL)
      return (tmp);
    tmp = tmp->prev;
  }
  return (tmp->next);
}

void    *check_in_free_list(size_t size)
{
  t_free  *tmp;

  tmp = freeStruct;
  while (tmp)
  {
    if (tmp->size >= size)
    {
      t_free *tmpToMalloc = tmp;
      if (tmpToMalloc->prev)
      {
        if (tmpToMalloc->next == NULL)
        {
          freeStruct->end = freeStruct->end->prev;
          freeStruct->end->next = NULL;
        }
        else
        {
          tmpToMalloc->next->prev = tmpToMalloc->prev;
          tmpToMalloc->prev->next = tmpToMalloc->next;
        }
      }
      else if (freeStruct->next == NULL)
        freeStruct = NULL;
      else
      {
        freeStruct->next->end = freeStruct->end;
        freeStruct = freeStruct->next;
        freeStruct->prev = NULL;
      }
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
            ptrNextMalloc = getNextMalloc(tmpToMalloc);
            if (ptrNextMalloc->prev == NULL)
            {
              ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
              mallocStruct = (t_malloc *) tmpToMalloc;
              mallocStruct->next = ptrNextMalloc;
              mallocStruct->end = ptrNextMalloc->end;
            }
            else
            {
              tmpToMalloc->prev = (t_free *) ptrNextMalloc->prev;
              tmpToMalloc->next = (t_free *) ptrNextMalloc;
              ptrNextMalloc->prev->next = (t_malloc *) tmpToMalloc;
              ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
            }
          }
          else
          {
            mallocStruct->end->next = (t_malloc *) tmpToMalloc;
            mallocStruct->end->next->prev = mallocStruct->end;
            mallocStruct->end = (t_malloc *) tmpToMalloc;
            mallocStruct->end->next = NULL;
          }
      }
      void *returnPtr = (void *) tmpToMalloc + sizeof(t_malloc);
      return (returnPtr);
    }
    tmp = tmp->next;
  }
  return (NULL);
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
    if (ptr < freeStruct->end && ptr > freeStruct)
    {

      t_free *tmp;
      tmp = getNextFree(ptr);
      if (tmp == (void *) ptr + ptr->size + sizeof(t_free))
      {
        ptr->size += tmp->size + sizeof(t_free);
        tmp->prev->next = ptr;
        ptr->prev = tmp->prev;
        ptr->next = tmp->next;
        if (tmp->next)
          tmp->next->prev = ptr;
        else
          freeStruct->end = ptr;
        if (ptr->prev == (void*) ptr - (ptr->prev->size + sizeof(t_free)))
        {
          ptr->prev->size += ptr->size + sizeof(t_free);
          ptr->prev->next = ptr->next;
          (ptr->next ? ptr->next->prev = ptr->prev : (freeStruct->end = ptr->prev));
        }
      }
     else if (tmp->prev && tmp->prev == (void*) ptr - (tmp->prev->size + sizeof(t_free)))
        tmp->prev->size += ptr->size + sizeof(t_free);
      else
      {
        ptr->next = tmp;
        ptr->prev = tmp->prev;
        tmp->prev->next = ptr;
        tmp->prev = ptr;
      }
    }
    else if (ptr > freeStruct->end)
    {
      if ((void *) freeStruct->end + freeStruct->end->size + sizeof(t_malloc) == (void *) ptr)
      {
        freeStruct->end->size += ptr->size + sizeof(t_malloc);
        ptr->prev = NULL;
        ptr->next = NULL;
      }
      else
      {
        freeStruct->end->next = ptr;
        freeStruct->end->next->prev = freeStruct->end;
        freeStruct->end = ptr;
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
}

void		free(void *ptr)
{
  t_malloc *tmp;

  if (ptr == NULL)
    return;
  //pthread_mutex_lock(&lock_mutex);
/*  my_putstr("free : ");
  printpointer(ptr - sizeof(t_malloc));
  my_putstr("\n"); */
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
  //pthread_mutex_unlock(&lock_mutex);
}
