/*
** malloc.h for malloc in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Wed Jan 25 18:35:39 2017
** Last update	Thu Jan 26 18:39:03 2017 Full Name
*/

#ifndef             MALLOC_H_
#define             MALLOC_H_

#include            <unistd.h>
#include            <stdbool.h>

typedef struct      s_malloc
{
  struct s_malloc   *next;
  int               size;
  bool              isFree;
}                   t_malloc;

#endif /* !MALLOC_H_ */
