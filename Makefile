CC=gcc
GFLAGS= -Werror -Wextra -Wall

NAME=mini
EXT_MOD=external_fonction

# Module readline : export EXT_F=readline

EXT_SRCS= main.c
EXT_OBJ= $(EXT_SRCS:.c=.o)


$(NAME): $(EXT_OBJ)
	$(CC)  $(EXT_OBJ) -o $(NAME)


clean:
	rm -rf $(EXT_OBJ)

fclean: clean
	rm -rf $(NAME)