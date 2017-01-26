/*
** utils.c for utils in /home/gastal_r/rendu/PSU_2016_malloc
** 
** Made by 
** Login   <gastal_r>
** 
** Started on  Tue Jan 24 14:19:22 2017 
** Last update Wed Jan 25 10:30:38 2017 
*/

#include	<unistd.h>
#include	"utils.h"
#include	<stdio.h>

void		malloc()
{
  printf("Hello world!!!\n");
}

int		my_strlen(char *str)
{
  int	i;

  i = -1;
  while (str[++i]);
  return (i);
}

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		my_putstr(char *str)
{
  write (1, str, my_strlen(str));
}
