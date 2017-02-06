##
## Makefile for Makefile in /home/gastal_r/rendu/PSU_2016_malloc
##
## Made by
## Login   <gastal_r>
##
## Started on  Fri Jan 27 12:28:44 2017
## Last update Mon Feb  6 12:10:54 2017 Juliani Renaud
##

CC				=       gcc -g -g3

RM				=       rm -rf

CFLAGS		=				-Wall -Wextra -W -fPIC -lpthread
CFLAGS		=				-I./include
LFLAGS		=				-shared

NAME			=				libmy_malloc.so

SRCS			=				src/malloc.c \
									src/utils.c	\
									src/free.c \
									src/printpointer.c \
									src/add_to_free.c \
									src/push_back_fct.c \
									src/fct_free.c

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
