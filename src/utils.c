/*
** utils.c for utils in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:19:22 2017
** Last update	Fri Feb 10 23:19:09 2017 Full Name
*/

#include        "utils.h"

void		print_pointer(void *nbs)
{
  size_t	div;
  size_t	nb;
  char		*base;

  nb = (size_t)nbs;
  base = "0123456789ABCDEF";
  div = 1;
  my_putstr("0x");
  while ((nb / div) >= 16)
    div = div * 16;
  while (div > 0)
    {
      write (1, &base[(nb / div) % 16], 1);
      div = div / 16;
    }
}

void		my_putnbr_unsigned(size_t nb)
{
  size_t		i;
  size_t		x;

  i = 1;
  while ((nb / i) >= 10)
    i = i * 10;
  while (i != 0)
    {
      x = ((nb / i) % 10) + 48;
      write(1, &x, 1);
      i = i / 10;
    }
}

int		my_strlen(char *str)
{
  int		i;

  i = -1;
  while (str[++i]);
  return (i);
}

void		my_putstr(char *str)
{
  write (1, str, my_strlen(str));
}
