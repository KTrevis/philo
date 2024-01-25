NAME = philo

SRCS = main.c init.c utils.c ft_atoi.c ft_calloc.c threads.c routine.c print.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -g3

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	cc $(CFLAGS) -c $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
