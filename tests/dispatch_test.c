#include "ctest.h"
#include "../src/parser/dispatcher.h"

CTEST(dispatch_test, echo_true)
{
	t_command command = {
							.code = ECHO,
							.argv = NULL
						};

	const t_command command_table[] = {command};
	const char *input = "test";
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, command_table));
}

CTEST(dispatch_test, unknown_command)
{
	t_command command = {
							.code = INVALID,
							.argv = NULL
						};

	const t_command command_table[] = {command};
	const char *input = "djweiojidowe";
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, command_table));
}