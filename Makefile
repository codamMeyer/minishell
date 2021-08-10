MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
CC=gcc
CFLAGS=-ggdb3 -Wall -Wextra -Werror
INC_PATH=-I./src -I./libft
LDFLAGS= -lreadline -L./libft -lft
LIBFT_PATH = libft/

MINISHELL_INCS= 						\
	src/defines.h						\
	src/parser/parser.h					\
	src/output/prompt.h					\
	src/parser/dispatcher.h				\
	src/commands/commands.h				\
	src/commands/echo_utils.h			\
	src/commands/echo_handle_quotes.h	\

MINISHELL_src= 							\
	src/parser/parser.c					\
	src/output/prompt.c					\
	src/parser/parser_utils.c			\
	src/parser/dispatcher.c				\
	src/commands/exit_command.c			\
	src/commands/echo_command.c			\
	src/commands/pwd_command.c			\
	src/commands/echo_utils.c			\
	src/commands/echo_handle_quotes.c	\

TEST_FILES=					\
	tests/main.c 			\
	tests/parser_test.c		\
	tests/dispatch_test.c	\
	tests/echo_test.c	\
	tests/pwd_test.c	\

MINISHELL_OBJS=$(MINISHELL_src:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS)
		make -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(INC_PATH) main.c -o $@ $^ $(LDFLAGS)

%.o: %.c $(MINISHELL_INCS)
	@$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

test_run: test
	./$(TEST_NAME)

test: $(MINISHELL_OBJS) $(TEST_FILES)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INC_PATH) $(MINISHELL_OBJS) $(TEST_FILES) -o $(TEST_NAME) $(LDFLAGS)

acceptance_test: $(MINISHELL)
	python3 tests/acceptance/main.py

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(MINISHELL_OBJS)

re: fclean all

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(TEST_NAME)

.PHONY: all clean fclean re test libftprintf
