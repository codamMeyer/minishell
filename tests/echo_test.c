#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/parser/parser.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>


int buffer_size_echo = 4096;
char echo_buf1[4096];

CTEST_DATA(echo_test)
{
	t_command command;
};

CTEST_SETUP(echo_test)
{
	data->command.code = ECHO,
	bzero(&echo_buf1[0], buffer_size_echo);
};

CTEST_TEARDOWN(echo_test)
{
	(void)data;
};

void	write_to_buf(const char *string_to_write)
{
	const int len = strlen(string_to_write);
	bzero(&echo_buf1[0], buffer_size_echo);
	strncpy(&echo_buf1[0], string_to_write, len);
}

CTEST2(echo_test, empty_str)
{
	char *input[2] = {NULL};
	data->command.arguments = input;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("\n", &echo_buf1[0]);
}
