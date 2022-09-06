NAME = philo
CFLAGS ?= -Wall -Wextra -Werror
# -fsanitize=address -g
CC = gcc

HEADERFILES = include/philo.h

SRC_FILES = main.c\

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