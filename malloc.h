/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Thu Jan 26 11:59:38 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

typedef struct      s_malloc
{
  struct s_malloc   *allocated;
  int               size;
  void	            *next;
}                   t_malloc;

typedef struct      s_free
{
  struct s_free     *allocated;
  int               size;
  void	            *next;
}                   t_free;


#endif /* !MALLOC_H_ */
