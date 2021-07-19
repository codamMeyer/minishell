MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
CC=gcc
CFLAGS=-Wall -Wextra -Werror
TEST_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./src
LDFLAGS= -lreadline

MINISHELL_INCS= 				\
	src/defines.h				\
	src/parser/parser.h			\
	src/output/prompt.h			\
	src/parser/dispatcher.h		\
	src/commands/commands.h		\

MINISHELL_src= 					\
	src/parser/parser.c			\
	src/output/prompt.c			\
	src/parser/parser_utils.c	\
	src/parser/dispatcher.c		\
	src/commands/exit_command.c	\

TEST_FILES=					\
	tests/main.c 			\
	tests/parser_test.c		\
	tests/dispatch_test.c	\

MINISHELL_OBJS=$(MINISHELL_src:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS)
		$(CC) $(CFLAGS) $(INC_PATH) main.c  -o $@ $^ $(LDFLAGS)

%.o: %.c $(MINISHELL_INCS)
	@$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

test_run: test
	./$(TEST_NAME)

test: $(MINISHELL_OBJS) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(MINISHELL_OBJS) $(TEST_FILES) -o $(TEST_NAME)

acceptance_test: $(MINISHELL)
	./tests/acceptance/exit_feature_test.py
	./tests/acceptance/echo_feature_test.py
	@rm tests/acceptance/*.txt

clean:
	rm -f $(MINISHELL_OBJS)

re: fclean all

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(TEST_NAME)

.PHONY: all clean fclean re test libftprintf
