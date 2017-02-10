/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Fri Feb 10 23:45:59 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <pthread.h>
#include            <string.h>

#include            "utils.h"

#if                 __x86_64__
#define             ALIGN 8
#else
#define             ALIGN 4
#endif

#define             PAGESIZE sysconf  (_SC_PAGESIZE)
#define             MALLOC_FLAG       'M'
#define             FREE_FLAG         'F'

typedef struct      s_malloc
{
  struct s_malloc   *next;
  struct s_malloc   *prev;
  size_t            size;
  char              flag;
}                   t_malloc;

typedef struct      s_free
{
  struct s_free     *next;
  struct s_free     *prev;
  size_t            size;
  char              flag;
}                   t_free;

typedef struct      s_core
{
  struct s_malloc   *mEnd;
  struct s_free     *fEnd;
  struct s_malloc   *mList;
  struct s_free     *fList;
}                   t_core;

t_core              *coreStruct;

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
void	              *init_malloc_head(size_t, size_t);
void			          free_delete_end(t_malloc *);
int                 get_multiple(int nb);
void	              init_mutex();

#endif              /* !MALLOC_H_ */
