/*
** fct_free.c for malloc in /home/julian_r/rendu/systeme_unix/PSU_2016_malloc
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Mon Feb  6 10:58:07 2017 Juliani Renaud
** Last update Mon Feb  6 11:36:29 2017 Juliani Renaud
*/

#include "malloc.h"

extern	t_malloc	*mallocStruct;
extern	t_free		*freeStruct;

t_free		*fracturation(size_t size, t_free *tmpToMalloc, t_free *tmpNext)
{
  tmpNext = (void *) tmpToMalloc + size + sizeof(t_free);
  tmpNext->size = tmpToMalloc->size - (size + sizeof(t_free));
  tmpToMalloc->size = size;
  tmpNext->prev = tmpToMalloc;
  tmpNext->next = tmpToMalloc->next;
  if (tmpToMalloc->next)
    tmpToMalloc->next->prev = tmpNext;
  else
    freeStruct->end = tmpNext;
  tmpToMalloc->next = tmpNext;
  tmpNext->c = FREE_FLAG;
  return (tmpNext);
}

void		removeFree(t_free *tmpToMalloc)
{
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
  return;
}

void		addFreeToMalloc2(t_free *tmpToMalloc)
{
  t_malloc *ptrNextMalloc;
  ptrNextMalloc = getNextMalloc(tmpToMalloc);
  if (ptrNextMalloc->prev == NULL)
    {
      ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
      mallocStruct = (t_malloc *) tmpToMalloc;
      mallocStruct->next = ptrNextMalloc;
      mallocStruct->end = ptrNextMalloc->end;
      mallocStruct->prev = NULL;
    }
  else
    {
      tmpToMalloc->prev = (t_free *) ptrNextMalloc->prev;
      tmpToMalloc->next = (t_free *) ptrNextMalloc;
      ptrNextMalloc->prev->next = (t_malloc *) tmpToMalloc;
      ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
    }
}

void		addFreeToMalloc(t_free *tmpToMalloc)
{
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
	addFreeToMalloc2(tmpToMalloc);
      else
	{
	  mallocStruct->end->next = (t_malloc *) tmpToMalloc;
	  mallocStruct->end->next->prev = mallocStruct->end;
	  mallocStruct->end = (t_malloc *) tmpToMalloc;
	  mallocStruct->end->next = NULL;
	}
    }
  tmpToMalloc->c = MALLOC_FLAG;
}
