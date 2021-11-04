MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
MINISHELL_ASAN=$(MINISHELL)_asan
CC=clang
CFLAGS=-ggdb3 -Wall -Wextra -Werror
CFLAGS_ASAN=$(CFLAGS) -fsanitize=leak
INC_PATH=-I./src -I./libft -I ~/.brew/opt/readline/include
LDFLAGS= -L ~/.brew/opt/readline/lib -l readline  -L ./libft -lft 
LIBFT_PATH = libft/

MINISHELL_INCS= 						\
	src/defines.h						\
	src/syntax/check_syntax.h			\
	src/syntax/check_quotes_syntax.h	\
	src/syntax/redirection_syntax.h		\
	src/syntax/write_errors.h			\
	src/parser/parser.h					\
	src/parser/command_table.h			\
	src/parser/parse_redirection.h		\
	src/output/prompt.h					\
	src/output/write_to_std.h			\
	src/executor/run_commands.h			\
	src/executor/executor_utils.h		\
	src/executor/redirection.h			\
	src/parser/here_doc.h				\
	src/parser/dispatcher.h				\
	src/parser/get_executable_path.h	\
	src/commands/commands.h				\
	src/commands/echo_utils.h			\
	src/commands/quotes.h				\
	src/commands/buffer.h				\
	src/env/environment.h				\
	src/env/env_utils.h					\
	src/env/export_utils.h				\
	src/signals/signals.h				\
	src/env/sort_env.h					\
	src/env/env_for_exec.h				\
	src/errors/errors.h					\
	src/errors/exit_code.h				\

MINISHELL_SRC= 							\
	src/syntax/check_syntax.c			\
	src/syntax/check_quotes_syntax.c	\
	src/syntax/redirection_syntax.c		\
	src/syntax/redirect_syntax_utils.c	\
	src/syntax/write_errors.c			\
	src/parser/parser.c					\
	src/output/prompt.c					\
	src/output/write_to_std.c			\
	src/executor/run_commands.c			\
	src/executor/executor_utils.c		\
	src/executor/redirection.c			\
	src/executor/redirection_utils.c	\
	src/parser/parser_utils.c			\
	src/parser/command_table.c			\
	src/parser/command_table_utils.c	\
	src/parser/dispatcher.c				\
	src/parser/get_executable_path.c	\
	src/parser/parse_redirection.c		\
	src/parser/parse_redirect_utils.c	\
	src/parser/here_doc.c				\
	src/parser/file_utils.c				\
	src/commands/exit_command.c			\
	src/commands/echo_command.c			\
	src/commands/echo_utils.c			\
	src/commands/quotes.c				\
	src/commands/buffer.c				\
	src/commands/pwd_command.c			\
	src/commands/environment_commands.c	\
	src/commands/cd_command.c			\
	src/env/environment.c				\
	src/env/environment_utils.c			\
	src/env/export_handle_key.c			\
	src/env/export_handle_value.c		\
	src/env/export_utils.c				\
	src/env/env_utils.c					\
	src/signals/signals.c				\
	src/signals/heredoc_signal.c		\
	src/env/sort_env.c					\
	src/env/env_for_exec.c				\
	src/errors/errors.c					\
	src/errors/exit_code.c				\

TEST_FILES=								\
	tests/main.c 						\
	tests/syntax_checker_tests.c 		\
	tests/parser_test.c					\
	tests/echo_test.c					\
	tests/pwd_test.c					\
	tests/unknown_test.c				\
	tests/get_executable_path_test.c	\
	tests/redirection_tests.c			\
	tests/pipe_test.c					\
	tests/env_api_test.c				\
	tests/env_for_execve_test.c			\
	tests/sort_env_test.c				\
	tests/redirection_tests.c			\
	tests/syntax_redirection_tests.c	\
	tests/syntax_checker_test.c			\

MINISHELL_OBJS=$(MINISHELL_SRC:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS) main.c
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INC_PATH) -o $@ $^ $(LDFLAGS)

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
	$(CC) $(CFLAGS_ASAN) -fsanitize=address $(INC_PATH) main.c -o $(MINISHELL_ASAN) $^ $(LDFLAGS)

acceptance_test_asan: $(MINISHELL_ASAN)
	./tests/acceptance/acceptance_test.sh asan

acceptance_test: $(MINISHELL)
	./tests/acceptance/acceptance_test.sh

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
