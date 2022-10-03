NAME = philo

SRC_DIR = srcs/
OBJ_DIR = ojbs/
INCLUDE = includes

CC = gcc
BASE_FLAGS = -Wall -Wextra -Werror -MMD -MP
THREAD_FLAGS = -pthread
CFLAGS = $(BASE_FLAGS) -I $(INCLUDE) $(THREAD_FLAGS)
DEBUG_FLAGS = -g

SRCS = $(shell find $(SRC_DIR) -name '*.c' | xargs basename -a)
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

DEPENDS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	if [ ! -d $(OBJ_DIR) ];then mkdir $(OBJ_DIR); fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -fsanitize=address $(DEBUG_FLAGS)
debug: re

leak: CFLAGS += $(DEBUG_FLAGS)
leak: re

.PHONY: all clean fclean re debug leak
