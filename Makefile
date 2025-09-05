OS= $(shell uname)
ifeq ($(OS), Darwin)
	CC=cc
else
	CC=gcc
endif

GFLAGS= -Werror -Wextra -Wall -g
BRANCH= $(shell git branch --show-current )
NAME=bin/*
NAME_TEST=bin/test
EXT_MOD=external_fonction
LIB= -Llibft -lft -lreadline
# Module readline : export EXT_F=readline

EXT_SRCS= 		srcs/main.c \
				srcs/tokeniser/tokeniser.c \
				srcs/ast/ast.c \
				srcs/tokeniser/tokeniser_utils.c

TEST_SRCS = 	test/external_fonction/dup.c  \
 				test/external_fonction/readline.c\
				test/main_test.c

EXT_OBJ= $(EXT_SRCS:%.c=%.o)
TEST_OBJ= $(TEST_SRCS:%.c=%.o)
#########
#revoir cette parti

%.o:%.c
	@$(CC) $(GFLAGS) $< -c -o $@
#########

$(NAME): $(EXT_OBJ)
	@$(CC) $(EXT_OBJ)  $(LIB) -o $(NAME)

run: $(NAME)
ifeq ($(OS), Darwin)
	@./$(NAME)
else
	@valgrind --leak-check=full --log-file=valgrind/valgrind.log ./$(NAME)
endif

test: $(TEST_OBJ)
	@$(CC) $(TEST_OBJ) $(LIB) -o $(NAME_TEST)
	@valgrind --leak-check=full --read-var-info=yes --track-fds=yes --log-file=valgrind/valgrind_test.log ./$(NAME_TEST)

clean:
	rm -rf $(EXT_OBJ)
	rm -rf $(TEST_OBJ)
	rm -f valgrind/valgrind.log
	rm -f valgrind/test/valgrind_test.log

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

git:
	git add .
	git commit -m $(COM)
	git push origin $(BRANCH)

lib:
	cd libft && make fclean && make bonus && make clean
n:
	echo $(CC)

.phony:
	re lib git clean fclean