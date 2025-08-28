NAME = PHILO
#relink var düzelt
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = arg_error_check.c assignment.c init_destroy_mutex.c create_philo.c \
time_functions.c routine.c saying_act.c dead_control.c main.c

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o philosophers

clean:
	rm -r philosophers

fclean: clean

re: fclean all