/*
** add_to_free.c for free in /home/julian_r/rendu/systeme_unix/PSU_2016_malloc
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Mon Feb  6 11:42:28 2017 Juliani Renaud
** Last update Mon Feb  6 11:58:00 2017 Juliani Renaud
*/

#include "malloc.h"

extern	t_malloc	*mallocStruct;
extern	t_free		*freeStruct;

void			add_middle2(t_free *tmp, t_free *ptr)
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
      (ptr->next ? ptr->next->prev = ptr->prev :
       (freeStruct->end = ptr->prev));
    }
  memset(tmp, 0, sizeof(t_free));
}

void			add_middle(t_free *ptr)
{
  t_free *tmp;
  tmp = getNextFree(ptr);
  if (tmp == (void *) ptr + ptr->size + sizeof(t_free))
    add_middle2(tmp, ptr);
  else if (tmp->prev && tmp->prev == (void*) ptr -
	   (tmp->prev->size + sizeof(t_free)))
    {
      tmp->prev->size += ptr->size + sizeof(t_free);
      memset(ptr, 0, sizeof(t_free));
    }
  else
    {
      ptr->next = tmp;
      ptr->prev = tmp->prev;
      tmp->prev->next = ptr;
      tmp->prev = ptr;
    }
}

void			add_end(t_free *ptr)
{
  if ((void *) freeStruct->end + freeStruct->end->size
      + sizeof(t_free) == (void *) ptr)
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

void			free_extend()
{
  mallocStruct->next->end = mallocStruct->end;
  mallocStruct = mallocStruct->next;
  mallocStruct->prev = NULL;
}
