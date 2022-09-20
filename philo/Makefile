NAME = philo
CFLAGS ?= -Wall -Wextra -Werror -fsanitize=address -g 
# -fsanitize=address -g 
# -fsanitize=thread -g (for data races)
CC = gcc

HEADERFILES = include/philo.h

SRC_FILES = main.c parser.c initialize.c philosopher.c clean.c\
			time.c message.c tasks.c\

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix obj/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJS) $(HEADERFILES)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

obj/%.o: src/%.c 
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
#No one should die:
#	./philo 4 800 200 2147483647
#Only one and should die
	./philo 1 800 200 200
#No one should die
#	./philo 5 800 200 200
#7 times everyone to eat at least
#	./philo 5 800 200 200 7 | GREP eating > outfile
#no one should die
#	./philo 4 410 200 200
#One should die
#	./philo 4 310 200 100


.PHONY: clean fclean re play