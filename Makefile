##
## Makefile for Makefile in /home/gastal_r/rendu/PSU_2016_malloc
##
## Made by
## Login   <gastal_r>
##
## Started on  Fri Jan 27 12:28:44 2017
## Last update Tue Feb  7 15:02:06 2017 
##

CC		=       gcc

RM		=       rm -rf

CFLAGS		+=	-Wall -Wextra -W -Werror -fPIC -lpthread
CFLAGS		+=	-I./include
LDFLAGS		+=	-shared

NAME		=	libmy_malloc.so

SRCS		=	src/malloc.c		\
			src/utils.c		\
			src/free.c		\
			src/add_to_free.c	\
			src/push_back_fct.c	\
			src/fct_free.c		\
			src/realloc.c		\
			src/show_func.c

OBJS		=	$(SRCS:.c=.o)

all		:       $(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean		:
			$(RM) $(OBJS)

fclean		:       clean
			$(RM) $(NAME)

re		:       fclean all

.PHONNY		:       all clean fclean re
