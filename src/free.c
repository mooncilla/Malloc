/*
** free.c for free in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Sat Feb  4 02:37:06 2017
** Last update	Mon Feb 06 13:48:29 2017 Full Name
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

      // Debut Fracturation des free //
      if ((int)((int) tmpToMalloc->size - ((int) size + sizeof(t_free))) >=  2)
      {
        t_free *tmpNext;
	tmpNext = NULL;
	tmpNext = fracturation(size, tmpToMalloc, tmpNext);
      }
      // Fin Fracturation des free //

      // Debut retirer le free des free //
      removeFree(tmpToMalloc);
      // Fin retirer le free des free //

      // Debut ajout du free dans le malloc //
      addFreeToMalloc(tmpToMalloc);
      // Fin ajout du free dans le malloc //

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
    // Debut ajout du free au mileu de la liste //
    if (ptr < freeStruct->end && ptr > freeStruct)
      add_middle(ptr);
    // Fin ajout du free au mileu de la liste //

    // Debut ajout du free à la fin de la liste //
    else if (ptr > freeStruct->end)
      add_end(ptr);
    // Fin ajout du free à la fin de la liste //

    // Debut ajout du free au début de la liste //
    else
    {
      ptr->end = freeStruct->end;
      ptr->prev = NULL;
      ptr->next = freeStruct;
      freeStruct->prev = ptr;
      freeStruct = ptr;
    }
    // Fin ajout du free au début de la liste //
  }
  ptr->c = FREE_FLAG;
}

void		free(void *ptr)
{
  t_malloc *tmp;

  if (ptr == NULL)
    return;
  pthread_mutex_lock(&lock_mutex);
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
    free_extend();
  add_to_free_list((t_free *) tmp);
  pthread_mutex_unlock(&lock_mutex);
}
