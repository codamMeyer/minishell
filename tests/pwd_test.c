#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/parser/dispatcher.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

int size1 = 4096;
char buf1[4096];

CTEST_DATA(pwd_test)
{
};

CTEST_SETUP(pwd_test)
{
	(void)data;
	bzero(&buf1[0], size1);
};

CTEST_TEARDOWN(pwd_test)
{
	(void)data;
};

void	write_to_buf1(const char *string_to_write)
{
	const int len = strlen(string_to_write);

	strncpy(&buf1[0], string_to_write, len);
}

CTEST2(pwd_test, success)
{
	(void)data;
    char expected[2048];
    getcwd(&expected[0], sizeof(expected));
    expected[ft_strlen(&expected[0])] = '\n';

	ASSERT_EQUAL(SUCCESS, pwd_command(write_to_buf1));
	ASSERT_STR(&expected[0], &buf1[0]);
}