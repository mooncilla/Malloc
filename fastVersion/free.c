/*
** free.c for free in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Sat Feb  4 02:37:06 2017
** Last update	Sat Feb 04 03:34:03 2017 Full Name
*/

#include  "malloc.h"

extern    t_malloc    *mallocStruct;

void    *check_in_free_list(size_t size)
{
  t_malloc  *tmp;

  tmp = mallocStruct;
  while (tmp)
  {
    if (tmp->isFree && tmp->size >= size)
    {
      tmp->isFree = false;
      //show_alloc_mem();
      return ((void*)tmp + sizeof(t_malloc));
    }
    tmp = tmp->next;
  }
  return (NULL);
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
  tmp->isFree = true;
  memset(ptr, 0, tmp->size);
  //pthread_mutex_unlock(&lock_mutex);
}
