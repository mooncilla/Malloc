/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Fri Jan 27 19:05:07 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <unistd.h>
#include            <stdbool.h>

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
void   *malloc(size_t size);
void	  free(void *);

#endif /* !MALLOC_H_ */
