/*
** utils.c for utils in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:19:22 2017
** Last update	Tue Jan 31 00:18:47 2017 Full Name
*/

#include	<unistd.h>
#include	"utils.h"
#include	<stdio.h>
#include <string.h>
int     my_putnbr(int nb)
{
  int   i;
  int   x;

  i = 1;
  if (nb < 0)
    {
      nb = nb * -1;
      my_putchar('-');
    }
  while ((nb / i) >= 10)
    i = i * 10;
  while (i != 0)
    {
      x = (nb / i) % 10;
      my_putchar(x + 48);
      i = i / 10;
    }
  return (0);
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
  write(2, &c, 1);
}

void		my_putstr(char *str)
{
  write (2, str, my_strlen(str));
}
