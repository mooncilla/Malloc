/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Sat Feb 04 03:21:08 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <unistd.h>
#include            <pthread.h>
#include            <string.h>
#include            <stdbool.h>

#define   PAGESIZE sysconf(_SC_PAGESIZE)

typedef struct      s_malloc
{
  struct s_malloc   *next;
  struct s_malloc   *end;
  bool							isFree;
  size_t            size;
}                   t_malloc;

pthread_mutex_t     lock_mutex;

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
void    *check_in_free_list(size_t size);

t_malloc    *mallocStruct;

#endif /* !MALLOC_H_ */
