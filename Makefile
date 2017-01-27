##
## Makefile for Makefile in /home/gastal_r/rendu/PSU_2016_malloc
##
## Made by
## Login   <gastal_r>
##
## Started on  Fri Jan 27 12:28:44 2017
## Last update Fri Jan 27 12:28:44 2017
##

CC				=       gcc

RM				=       rm -rf

CFLAGS		=				-Wall -Wextra -W -fPIC

LFLAGS		=				-shared

NAME			=				libmy_malloc.so

SRCS			=				malloc.c

OBJS			=				$(SRCS:.c=.o)

all				:       $(NAME)

$(NAME)		:
									$(CC) -c $(CFLAGS) $(SRCS)
									$(CC) $(LFLAGS) -o $(NAME) $(OBJS)

clean			:
									$(RM) $(OBJS)

fclean		:       clean
									$(RM) $(NAME)

re				:       clean fclean all

.PHONNY		:       all clean fclean re
