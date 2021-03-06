/*
** fct_free.c for malloc in /home/julian_r/rendu/systeme_unix/PSU_2016_malloc
**
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
**
** Started on  Mon Feb  6 10:58:07 2017 Juliani Renaud
** Last update	Fri Feb 10 01:43:21 2017 Full Name
*/

#include          "malloc.h"

extern t_core   *coreStruct;

t_free		        *fracturation(size_t size, t_free *tmpToMalloc)
{
  t_free          *tmpNext;

  tmpNext = (void *) tmpToMalloc + size + sizeof(t_free);
  tmpNext->size = tmpToMalloc->size - (size + sizeof(t_free));
  tmpToMalloc->size = size;
  tmpNext->prev = tmpToMalloc;
  tmpNext->next = tmpToMalloc->next;
  if (tmpToMalloc->next)
    tmpToMalloc->next->prev = tmpNext;
  else
    coreStruct->fEnd = tmpNext;
  tmpToMalloc->next = tmpNext;
  tmpNext->flag = FREE_FLAG;
  return (tmpNext);
}

void			removeFree(t_free *tmpToMalloc)
{
  if (tmpToMalloc->prev)
    {
      if (tmpToMalloc->next == NULL)
	{
	  coreStruct->fEnd = coreStruct->fEnd->prev;
	  coreStruct->fEnd->next = NULL;
	}
      else
	{
	  tmpToMalloc->next->prev = tmpToMalloc->prev;
	  tmpToMalloc->prev->next = tmpToMalloc->next;
	}
    }
  else if (coreStruct->fList->next == NULL)
    coreStruct->fList = NULL;
  else
    {
      coreStruct->fList = coreStruct->fList->next;
      coreStruct->fList->prev = NULL;
    }
  return ;
}

void			addFreeToMalloc2(t_free *tmpToMalloc)
{
  t_malloc		*ptrNextMalloc;

  ptrNextMalloc = getNextMalloc(tmpToMalloc);
  if (ptrNextMalloc->prev == NULL)
    {
      ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
      coreStruct->mList = (t_malloc *) tmpToMalloc;
      coreStruct->mList->next = ptrNextMalloc;
      coreStruct->mList->prev = NULL;
    }
  else
    {
      tmpToMalloc->prev = (t_free *) ptrNextMalloc->prev;
      tmpToMalloc->next = (t_free *) ptrNextMalloc;
      ptrNextMalloc->prev->next = (t_malloc *) tmpToMalloc;
      ptrNextMalloc->prev = (t_malloc *) tmpToMalloc;
    }
}

void			addFreeToMalloc(t_free *tmpToMalloc)
{
  if (coreStruct->mList == NULL)
    {
      coreStruct->mList = (t_malloc *) tmpToMalloc;
      coreStruct->mEnd = coreStruct->mList;
      coreStruct->mList->next = NULL;
      coreStruct->mList->prev = NULL;
    }
  else
    {
      if (coreStruct->mList && coreStruct->mEnd > (t_malloc *) tmpToMalloc)
	addFreeToMalloc2(tmpToMalloc);
      else
	{
	  coreStruct->mEnd->next = (t_malloc *) tmpToMalloc;
	  coreStruct->mEnd->next->prev = coreStruct->mEnd;
	  coreStruct->mEnd = (t_malloc *) tmpToMalloc;
	  coreStruct->mEnd->next = NULL;
	}
    }
  tmpToMalloc->flag = MALLOC_FLAG;
}
