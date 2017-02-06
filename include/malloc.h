/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Mon Feb 06 23:34:40 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <pthread.h>
#include            <string.h>

#include            "utils.h"

#define             PAGESIZE sysconf  (_SC_PAGESIZE)
#define             MALLOC_FLAG       'M'
#define             FREE_FLAG         'F'

typedef struct      s_malloc
{
  struct s_malloc   *next;
  struct s_malloc   *prev;
  struct s_malloc   *end;
  size_t            size;
  char              flag;
}                   t_malloc;

typedef struct      s_free
{
  struct s_free     *next;
  struct s_free     *prev;
  struct s_free     *end;
  size_t            size;
  char              flag;
}                   t_free;

t_malloc            *mallocStruct;
t_free              *freeStruct;

pthread_mutex_t     mutex_malloc;

void                *malloc(size_t size);
void                *realloc(void *ptr, size_t size);
void                *calloc(size_t nmemb, size_t size);
void	              free(void *);
void		            show_alloc_mem();
void                show_free_list();
size_t	            allow_right(size_t);
void                *check_in_free_list(size_t size);
t_malloc            *getNextMalloc(t_free *tmpToMalloc);
t_free	            *getNextFree(t_free *);
t_free	            *fracturation(size_t, t_free *);
void	              removeFree(t_free *);
void	              addFreeToMalloc(t_free *);
void	              add_end(t_free*);
void	              add_middle(t_free *);
void	              merging_block();
void                free_malloc_head();
void	              *push_if_null(size_t, size_t);

#endif              /* !MALLOC_H_ */
