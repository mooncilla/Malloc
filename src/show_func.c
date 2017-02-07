/*
** show_func.c for show_func in /home/gastal_r/rendu/PSU_2016_malloc/src
**
** Made by
** Login   <gastal_r>
**
** Started on  Mon Feb  6 18:47:14 2017
** Last update	Tue Feb 07 13:38:57 2017 Full Name
*/

#include        "malloc.h"

extern t_malloc	*mallocStruct;
extern t_free	*freeStruct;

void		show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = mallocStruct;
  my_putstr("break : ");
  print_pointer(sbrk(0));
  my_putstr("\n");
  while (tmp)
  {
    print_pointer((void *) tmp  + sizeof(t_malloc));
    my_putstr(" - ");
    print_pointer((void *) tmp  + sizeof(t_malloc) + tmp->size);
    my_putstr(" : ");
    my_putnbr_unsigned(tmp->size);
    my_putstr(" bytes\n");
    tmp = tmp->next;
  }
}

void		show_free_list()
{
  t_free	*tmp;

  tmp = freeStruct;
  my_putstr("freeList : ");
  my_putstr("\n");
  while (tmp)
  {
    print_pointer((void *) tmp  + sizeof(t_free));
    my_putstr(" - ");
    print_pointer((void *) tmp  + sizeof(t_free) + tmp->size);
    my_putstr(" : ");
    my_putnbr_unsigned(tmp->size);
    my_putstr(" bytes\n");
    tmp = tmp->next;
  }
}
