#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/parser/dispatcher.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

int size2 = 4096;
char buf_1[4096];
char buf_2[4096];
char buf_3[4096];

CTEST_DATA(unkown_command_test)
{
};

CTEST_SETUP(unkown_command_test)
{
	(void)data;
	bzero(&buf_1[0], size2);
	bzero(&buf_2[0], size2);
	bzero(&buf_3[0], size2);
};

CTEST_TEARDOWN(unkown_command_test)
{
	(void)data;
};

void	write_to_buf2(const char *string_to_write)
{
	const int len = strlen(string_to_write);
	static int i = 1;
	switch (i)
	{
	case 1:
		strncpy(&buf_1[0], string_to_write, len);
		break;
	case 2:
		strncpy(&buf_2[0], string_to_write, len);
		break;
	case 3:
		strncpy(&buf_3[0], string_to_write, len);
		break;
	}
	++i;
}

CTEST2(unkown_command_test, success)
{
	(void)data;
    const char *expected[3] = {"BestShellEver: ", "blah", ": command not found\n"};
	const char *input = "blah diedioweopdjeiowjdoijewoi";
	unknown_command(&input, write_to_buf2);
	ASSERT_STR(expected[0], &buf_1[0]);
	ASSERT_STR(expected[1], &buf_2[0]);
	ASSERT_STR(expected[2], &buf_3[0]);
}