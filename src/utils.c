/*
** utils.c for utils in /home/gastal_r/rendu/PSU_2016_malloc
**
** Made by
** Login   <gastal_r>
**
** Started on  Tue Jan 24 14:19:22 2017
** Last update	Mon Feb 06 16:25:49 2017 Full Name
*/

#include        "utils.h"

void		print_pointer(void *nbs)
{
  size_t	result;
  size_t	div;
  size_t	length;
  size_t	nb;
  char		*base;

  nb = (size_t)nbs;
  base = "0123456789ABCDEF";
  result = 0;
  div = 1;
  length = 16;
  my_putstr("0x");
  while ((nb / div) >= length)
    div = div * length;
  while (div > 0)
    {
      result = (nb / div) % length;
      write (2, &base[result], 1);
      div = div / length;
    }
}

void		my_putnbr(int nb)
{
  int		i;
  int		x;

  i = 1;
  if (nb < 0)
    {
      nb = nb * -1;
      write(2, "-", 1);
    }
  while ((nb / i) >= 10)
    i = i * 10;
  while (i != 0)
    {
      x = ((nb / i) % 10) + 48;
      write(2, &x, 1);
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
  write (2, str, my_strlen(str));
}
