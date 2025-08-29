NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = arg_error_check.c assignment.c init_destroy_mutex.c create_philo.c \
time_functions.c routine.c saying_act.c dead_control.c main.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o philo

clean:
	rm -rf philo

fclean: clean

re: fclean all