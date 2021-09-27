#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/parser/syntax_checker.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

char error_buffer[BUFFER_SIZE];

CTEST_DATA(quote_syntax_checker)
{
};

CTEST_SETUP(quote_syntax_checker)
{
	(void)data;
	bzero(&error_buffer[0], BUFFER_SIZE);
};

CTEST_TEARDOWN(quote_syntax_checker)
{
	(void)data;
};

void	write_error_to_buffer(const char *string_to_write)
{
	const int len = strlen(string_to_write);
	strncpy(&error_buffer[0], string_to_write, len);
}

CTEST2(quote_syntax_checker, one_quote)
{
	(void)data;
	const char *input = "echo   \" missing one quote";
	ASSERT_EQUAL(ERROR, is_missing_quotes(input, write_error_to_buffer));
	ASSERT_STR("Missing closing quote\n", &error_buffer[0]);
}

CTEST2(quote_syntax_checker, three_quote)
{
	(void)data;
	const char *input = "echo   \" missing \" one quote \"";
	ASSERT_EQUAL(ERROR, is_missing_quotes(input, write_error_to_buffer));
	ASSERT_STR("Missing closing quote\n", &error_buffer[0]);
}

CTEST2(quote_syntax_checker, one_double_one_single_quote)
{
	(void)data;
	const char *input = "echo   \" missing one quote '";
	ASSERT_EQUAL(ERROR, is_missing_quotes(input, write_error_to_buffer));
	ASSERT_STR("Missing closing quote\n", &error_buffer[0]);
}

CTEST2(quote_syntax_checker, two_pairs_of_quotes)
{
	(void)data;
	const char *input = "echo   \"missing\" \"one\" quote ";
	ASSERT_EQUAL(SUCCESS, is_missing_quotes(input, write_error_to_buffer));
}

CTEST2(quote_syntax_checker, no_quote)
{
	(void)data;
	const char *input = "echo   missing one quote ";
	ASSERT_EQUAL(SUCCESS, is_missing_quotes(input, write_error_to_buffer));
}