NAME = PHILO

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = 

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o philosofhers

clean:
	rm -r philosofhers

fclean: clean

re: fclean all