#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/parser/dispatcher.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>


int buffer_size_pwd = 4096;
char pwd_buf1[4096];
char pwd_buf2[4096];
char pwd_buf3[4096];
CTEST_DATA(pwd_test)
{
};

CTEST_SETUP(pwd_test)
{
	(void)data;
	bzero(&pwd_buf1[0], buffer_size_pwd);
	bzero(&pwd_buf2[0], buffer_size_pwd);
};

CTEST_TEARDOWN(pwd_test)
{
	(void)data;
};

void	write_to_buf1(const char *string_to_write)
{
	static int i = 0;
	const int len = strlen(string_to_write);
	
	if (i)
		strncpy(&pwd_buf2[0], string_to_write, len);
	else
		strncpy(&pwd_buf1[0], string_to_write, len);
	i++;
}

CTEST2(pwd_test, success)
{
	(void)data;
    char expected[2048];
    getcwd(&expected[0], sizeof(expected));
	t_command command;
	command.code = PWD;
	ASSERT_EQUAL(SUCCESS, pwd_command(command, write_to_buf1));
	ASSERT_STR(&expected[0], &pwd_buf1[0]);
	ASSERT_STR("\n", &pwd_buf2[0]);
}