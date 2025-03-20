NAME = philo

CMD = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

SRCS = \
	actions.c\
	atol.c\
	checks.c\
	exit.c\
	init.c\
	main.c\
	utils.c\
	validate.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CMD) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
