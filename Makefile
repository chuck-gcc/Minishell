CC= gcc
GFLAGS= -Werror -Wextra -Wall -g
BRANCH= $(shell git branch --show-current )
NAME=bin/mini
EXT_MOD=external_fonction

# Module readline : export EXT_F=readline

EXT_SRCS= srcs/main.c
EXT_OBJ= $(EXT_SRCS:%.c=%.o)

#########
#revoir cette parti

%.o:%.c
	$(CC) $(GFLAGS) $< -c -o $@

$(NAME): $(EXT_OBJ)
	$(CC) $(EXT_OBJ)  -Llibft -lft -lreadline -o $(NAME)


clean:
	rm -rf $(EXT_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

git:
	git add .
	git commit -m $(COM)
	git push origin $(BRANCH)

lib:
	cd libft && make fclean && make bonus && make clean

.phony:
	re lib git clean fclean