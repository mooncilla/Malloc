/*
** printpointer.c for printpointer in /home/gastal_r/rendu/PSU_2015_my_printf
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon Nov 16 11:00:49 2015 remi gastaldi
** Last update Fri Jan 27 11:09:19 2017 Juliani Renaud
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void	printpointer(void *nbs)
{
  size_t   result;
  size_t   div;
  size_t   length;
  size_t   nb;
  char	   *base;

  nb = (size_t)nbs;
  base = "0123456789abcdef";
  result = 0;
  div = 1;
  length = 16;
  my_putstr("0x");
  while ((nb / div) >= length)
    div = div * length;
  while (div > 0)
    {
      result = (nb / div) % length;
      my_putchar(base[result]);
      div = div / length;
    }
  my_putchar('\n');
}
