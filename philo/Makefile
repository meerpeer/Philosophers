NAME = philo
CFLAGS ?= -Wall -Wextra -Werror
# -fsanitize=address -g
# -fsanitizer=thread -g (for data races)
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

.PHONY: clean fclean re play