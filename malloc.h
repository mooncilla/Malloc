/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Mon Jan 30 22:43:46 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <unistd.h>
#include <string.h>

typedef struct      s_malloc
{
  struct s_malloc   *next;
  struct s_malloc   *prev;
  struct s_malloc   *end;
  size_t            size;
}                   t_malloc;

typedef struct      s_free
{
  struct s_free     *next;
  struct s_free     *prev;
  struct s_free     *end;
  size_t            size;
}                   t_free;

void		my_strlen(char *);
void		my_putchar(char);
void		my_putstr(char *);
void		printpointer(void *);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void	  free(void *);
void		show_alloc_mem();
int     my_putnbr(int nb);
void   *calloc(size_t nmemb, size_t size);
void   show_free_list();
#endif /* !MALLOC_H_ */
