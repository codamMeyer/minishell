MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
TEST_EXAMPLE=test_example
CC=gcc
CFLAGS=-Wall -Wextra -Werror -O3 -fsanitize=leak -fsanitize=address
TEST_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./src
LDFLAGS=

MINISHELL_INCS=\

MINISHELL_SRCS=\

TEST_FILES=					\
	tests/calculator.c	 	\
	tests/examples.c	 	\
	tests/main.c 			\

MINISHELL_OBJS=$(MINISHELL_SRCS:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS)
		$(CC) $(CFLAGS) $(INC_PATH) main.c  -o $@ $^ $(LDFLAGS)

%.o: %.c $(MINISHELL_INCS)
	@$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

test_example:
	@make fclean
	$(CC) $(TEST_CFLAGS) $(TEST_FILES) -o $(TEST_EXAMPLE)
	@./$(TEST_EXAMPLE)

test_run: test
	./$(TEST_NAME)

test_integration: $(MINISHELL)
	./tests/integration_test.py

test: $(MINISHELL_OBJS) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(MINISHELL_OBJS) $(TEST_FILES) -o $(TEST_NAME) $(LDFLAGS)

clean:
	rm -f $(MINISHELL_OBJS)

re: fclean all

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(TEST_NAME)
	rm -f $(TEST_EXAMPLE)
	rm -f norminette_result

.PHONY: all clean fclean re test libftprintf test_example
