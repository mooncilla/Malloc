/*
** free.c for free in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Sat Feb  4 02:37:06 2017
** Last update	Mon Feb 06 23:37:41 2017 Full Name
*/

#include          "malloc.h"

extern t_malloc   *mallocStruct;
extern t_free     *freeStruct;
extern pthread_mutex_t mutex_malloc;

t_free			*getNextFree(t_free *tmpToMalloc)
{
  t_free		*tmp;

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

void			*check_in_free_list(size_t size)
{
  t_free		*tmp;

  tmp = freeStruct;
  while (tmp)
  {
    if (tmp->size >= size)
    {
      if ((int)((int) tmp->size - ((int) size + sizeof(t_free))) >= 4)
	fracturation(size, tmp);
      removeFree(tmp);
      addFreeToMalloc(tmp);
      return ((void *) tmp + sizeof(t_malloc));
    }
    tmp = tmp->next;
  }
  return (NULL);
}

void			add_to_free_list(t_free *ptr)
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
      add_middle(ptr);
    else if (ptr > freeStruct->end)
      add_end(ptr);
    else
    {
      ptr->end = freeStruct->end;
      ptr->prev = NULL;
      ptr->next = freeStruct;
      freeStruct->prev = ptr;
      freeStruct = ptr;
    }
  }
  ptr->flag = FREE_FLAG;
}

void			free_delete_end(t_malloc *tmp)
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

void		        free(void *ptr)
{
  t_malloc		*tmp;

  pthread_mutex_lock(&mutex_malloc);
  if (ptr == NULL)
    {
      pthread_mutex_unlock(&mutex_malloc);
      return ;
    }
  tmp = ptr - sizeof(t_malloc);
  if (tmp->prev)
    free_delete_end(tmp);
  else if (mallocStruct->next == NULL)
    mallocStruct = NULL;
  else
    free_malloc_head();
  add_to_free_list((t_free *) tmp);
  pthread_mutex_unlock(&mutex_malloc);
}
