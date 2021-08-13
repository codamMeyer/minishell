#include "ctest.h"
#include "../src/parser/dispatcher.h"
#include "../libft/libft.h"

CTEST(dispatch_test, echo_true)
{
	const char *input = "test";
	t_command command = {
							.code = ECHO,
							.arg_len = 4,
							.arg.start = input,
							.arg.end = input + 4,
						};

	const t_command command_table[] = {command};
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, command_table));
}

CTEST(dispatch_test, unknown_command)
{
	const char *input = "djweiojidowe";
	t_command command = {
							.code = INVALID,
							.arg_len = 12,
							.arg.start = input,
							.arg.end = input + 12,
						};

	const t_command command_table[] = {command};
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, command_table));
}