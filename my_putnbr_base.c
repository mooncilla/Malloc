/*
** my_putnbr_base.c for my_putnbr_base in /home/gastal_r/rendu/Piscine_C_J06/ex_16
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Sat Nov 14 13:49:06 2015 remi gastaldi
** Last update Mon Feb 22 16:12:30 2016 remi gastaldi
*/

#include "my.h"

void	my_putnbr_base(int nb, char *base)
{
  int   result;
  int   div;
  int   length;

  result = 0;
  div = 1;
  length = my_strlen(base);
  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * -1;
    }
  while ((nb / div) >= length)
    div = div * length;
  while (div > 0)
    {
      result = (nb / div) % length;
      my_putchar(base[result]);
      div = div / length;
    }
}
