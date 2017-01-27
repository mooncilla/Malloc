/*
** printpointer.c for printpointer in /home/gastal_r/rendu/PSU_2015_my_printf
** 
** Made by remi gastaldi
** Login   <gastal_r@epitech.net>
** 
** Started on  Mon Nov 16 11:00:49 2015 remi gastaldi
** Last update Mon Feb 22 16:13:49 2016 remi gastaldi
*/

#include "my.h"

void	printpointer(va_list ap)
{
  my_putstr("0x");
  my_putnbr_base_t(va_arg(ap, size_t), "0123456789abcdef");
}
