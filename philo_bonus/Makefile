SRCS		= creating.c helps1.c main.c actions.c
DIR			= objs

HEADER		= philo.h

OBJS		= $(SRCS:.c=.o)

NAME		= philo_bonus

CC			= cc
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror -I.

all:	$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

%.o:			%.c $(HEADER)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
