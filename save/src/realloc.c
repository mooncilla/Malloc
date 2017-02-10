/*
** realloc.c for realloc in /home/gastal_r/rendu/PSU_2016_malloc/src
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Feb  7 15:00:57 2017
** Last update	Thu Feb 09 18:21:54 2017 Full Name
*/

#include	"malloc.h"

void		*realloc(void *ptr, size_t size)
{
  void		*tmp;
  t_malloc	*ptrStruct;

  size = get_multiple(size);
  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  if ((tmp = check_in_free_list(size)) == NULL)
    tmp = malloc(size);
  ptrStruct = ptr - sizeof(t_malloc);
  if (ptrStruct->size < size)
    tmp = memcpy(tmp, ptr, ptrStruct->size);
  else
    tmp = memcpy(tmp, ptr, size);
  free(ptr);
  return (tmp);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  size = get_multiple(size);
  ptr = malloc(nmemb * size);
  ptr = memset(ptr, 0, nmemb * size);
  return (ptr);
}
