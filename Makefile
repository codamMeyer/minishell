MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
MINISHELL_ASAN=$(MINISHELL)_asan
CC=clang
CFLAGS=-ggdb3 -Wall -Wextra -Werror
CFLAGS_ASAN=$(CFLAGS) -fsanitize=leak
INC_PATH=-I./src -I./libft
LDFLAGS= -lreadline -L./libft -lft
LIBFT_PATH = libft/

MINISHELL_INCS= 						\
	src/defines.h						\
	src/parser/parser.h					\
	src/parser/command_table.h			\
	src/output/prompt.h					\
	src/output/handle_pipes.h			\
	src/output/pipe_utils.h				\
	src/output/redirection.h			\
	src/parser/dispatcher.h				\
	src/parser/get_executable_path.h	\
	src/commands/commands.h				\
	src/commands/echo_utils.h			\
	src/commands/echo_handle_quotes.h	\

MINISHELL_SRC= 							\
	src/parser/parser.c					\
	src/output/prompt.c					\
	src/output/handle_pipes.c			\
	src/output/pipe_utils.c				\
	src/output/redirection.c			\
	src/parser/parser_utils.c			\
	src/parser/command_table.c			\
	src/parser/dispatcher.c				\
	src/parser/get_executable_path.c	\
	src/commands/exit_command.c			\
	src/commands/echo_command.c			\
	src/commands/pwd_command.c			\
	src/commands/echo_utils.c			\
	src/commands/echo_handle_quotes.c	\

TEST_FILES=								\
	tests/main.c 						\
	tests/parser_test.c					\
	tests/dispatch_test.c				\
	tests/echo_test.c					\
	tests/pwd_test.c					\
	tests/unknown_test.c				\
	tests/get_executable_path_test.c	\

MINISHELL_OBJS=$(MINISHELL_SRC:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS)
		make -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(INC_PATH) main.c -o $@ $^ $(LDFLAGS)

%.o: %.c $(MINISHELL_INCS)
	@$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

test_run: test
	./$(TEST_NAME)

test: $(MINISHELL_OBJS) $(TEST_FILES)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(INC_PATH) $(MINISHELL_OBJS) $(TEST_FILES) -o $(TEST_NAME) $(LDFLAGS)

test_asan: $(MINISHELL_SRC) $(TEST_FILES)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS_ASAN) $(INC_PATH) $(MINISHELL_SRC) $(TEST_FILES) -o test_asan $(LDFLAGS)
	./test_asan

$(MINISHELL_ASAN): $(MINISHELL_SRC)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS_ASAN) $(INC_PATH) main.c -o $(MINISHELL_ASAN) $^ $(LDFLAGS)

acceptance_test: $(MINISHELL)
	python3 tests/acceptance/main.py

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(MINISHELL_OBJS)

re: fclean all

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(TEST_NAME)
	rm -f test_asan
	rm -f $(MINISHELL_ASAN)

.PHONY: all clean fclean re test libftprintf
