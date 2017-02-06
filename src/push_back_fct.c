/*
** push_back_fct.c for malloc in /home/julian_r/rendu/systeme_unix/PSU_2016_malloc
** 
** Made by Juliani Renaud
** Login   <julian_r@epitech.net>
** 
** Started on  Mon Feb  6 11:58:49 2017 Juliani Renaud
** Last update Mon Feb  6 12:04:35 2017 Juliani Renaud
*/

#include "malloc.h"

extern	t_malloc	*mallocStruct;
extern	t_free		*freeStruct;

void			*push_if_null(size_t size, size_t currentPageSize)
{
  if (freeStruct)
    mallocStruct = (void *) freeStruct->end + freeStruct->end->size + sizeof(t_free)\
      ;
  else
    mallocStruct = sbrk(0) - currentPageSize;
  mallocStruct->size = size;
  mallocStruct->end = mallocStruct;
  mallocStruct->next = NULL;
  mallocStruct->prev = NULL;
  mallocStruct->c = MALLOC_FLAG;
  void *ptr = (void *) mallocStruct + sizeof(t_malloc);
  return (ptr);
}

size_t          allow_right(size_t      needed)
{
  size_t        right;

  right = PAGESIZE * 2;
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