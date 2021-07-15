MINISHELL=minishell
TEST_NAME=$(MINISHELL)_test
CC=gcc
CFLAGS=-Wall -Wextra -Werror
TEST_CFLAGS=-ggdb3 $(CFLAGS)
INC_PATH=-I./src
LDFLAGS= -lreadline

MINISHELL_INCS= 				\
	srcs/defines.h				\
	srcs/parser/parser.h		\
	srcs/output/prompt.h		\
	srcs/parser/dispatcher.c	\

MINISHELL_SRCS= 				\
	srcs/parser/parser.c		\
	srcs/output/prompt.c		\
	srcs/parser/parser_utils.c	\
	srcs/parser/dispatcher.c	\

TEST_FILES=					\
	tests/main.c 			\
	tests/parser_test.c		\
	tests/dispatch_test.c			\

MINISHELL_OBJS=$(MINISHELL_SRCS:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_OBJS)
		$(CC) $(CFLAGS) $(INC_PATH) main.c  -o $@ $^ $(LDFLAGS)

%.o: %.c $(MINISHELL_INCS)
	@$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

test_run: test
	./$(TEST_NAME)
	# norminette srcs/

test: $(MINISHELL_OBJS) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(MINISHELL_OBJS) $(TEST_FILES) -o $(TEST_NAME) $(LDFLAGS)

test_integration: $(MINISHELL)
	./tests/integration_test.py

clean:
	rm -f $(MINISHELL_OBJS)

re: fclean all

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(TEST_NAME)

.PHONY: all clean fclean re test libftprintf test_example
