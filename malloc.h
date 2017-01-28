/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Sat Jan 28 19:43:14 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <unistd.h>
#include            <stdbool.h>
#include <string.h>

typedef struct      s_malloc
{
  struct s_malloc   *next;
  size_t            size;
  bool              isFree;
}                   t_malloc;

void		my_strlen(char *);
void		my_putchar(char);
void		my_putstr(char *);
void		printpointer(void *);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void	  free(void *);
void		show_alloc_mem();
int     my_putnbr(int nb);

#endif /* !MALLOC_H_ */
