/*
** my_putnbr_base_t.c for my_putnbr_base in /home/gastal_r/rendu/PSU_2015_my_printf
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon Nov 16 13:35:08 2015 remi gastaldi
** Last update Mon Feb 22 16:14:35 2016 remi gastaldi
*/

#include "my.h"

void	my_putnbr_base_t(size_t nb, char *base)
{
  size_t	result;
  size_t   div;
  size_t   length;

  result = 0;
  div = 1;
  length = my_strlen(base);
  while ((nb / div) >= length)
    div = div * length;
  while (div > 0)
    {
      result = (nb / div) % length;
      my_putchar(base[result]);
      div = div / length;
    }
}
