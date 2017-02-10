/*
** free.c for free in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Sat Feb  4 02:37:06 2017
** Last update	Fri Feb 10 01:31:29 2017 Full Name
*/

#include          "malloc.h"

extern t_core   *coreStruct;
extern pthread_mutex_t mutex_malloc;

t_free			*getNextFree(t_free *tmpToMalloc)
{
  t_free		*tmp;

  tmp = coreStruct->fEnd;
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

  tmp = coreStruct->fList;
  while (tmp)
  {
    if (tmp->size >= size)
    {
      if ((int)((int) tmp->size - ((int) size + sizeof(t_free))) >= ALIGN)
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
  if (coreStruct->fList == NULL)
  {
    coreStruct->fList = ptr;
    coreStruct->fEnd = coreStruct->fList;
    coreStruct->fList->next = NULL;
    coreStruct->fList->prev = NULL;
  }
  else
  {
    if (ptr < coreStruct->fEnd && ptr > coreStruct->fList)
      add_middle(ptr);
    else if (ptr > coreStruct->fEnd)
      add_end(ptr);
    else
    {
      ptr->prev = NULL;
      ptr->next = coreStruct->fList;
      coreStruct->fList->prev = ptr;
      coreStruct->fList = ptr;
    }
  }
  ptr->flag = FREE_FLAG;
}

void			free_delete_end(t_malloc *tmp)
{
  if (tmp->next == NULL)
    {
      coreStruct->mEnd = coreStruct->mEnd->prev;
      coreStruct->mEnd->next = NULL;
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
  if (ptr == NULL || ((t_malloc*)(ptr - sizeof(t_malloc)))->flag == FREE_FLAG)
    {
      pthread_mutex_unlock(&mutex_malloc);
      return ;
    }
  tmp = ptr - sizeof(t_malloc);
  if (tmp->prev)
    free_delete_end(tmp);
  else if (coreStruct->mList->next == NULL)
    coreStruct->mList = NULL;
  else
    free_malloc_head();
  add_to_free_list((t_free *) tmp);
  pthread_mutex_unlock(&mutex_malloc);
}
