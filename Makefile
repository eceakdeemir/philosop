NAME = PHILO

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = arg_error_check.c assignment.c init_destroy_mutex.c main.c

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o philosophers

clean:
	rm -r philosofhers

fclean: clean

re: fclean all