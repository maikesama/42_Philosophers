NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

SRCS = philo.c\
		utils.c\
		init.c\
		state.c\
		routine.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[34mcompiled successfully\033[0m"

clean:
	@rm -f $(NAME) $(OBJS)
	@echo "\033[33mclean completed\033[0m"

fclean: clean

re: fclean all