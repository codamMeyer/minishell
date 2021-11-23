#include "ctest.h"
#include "../src/commands/commands.h"
#include "../src/syntax/check_quotes_syntax.h"
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

CTEST2(quote_syntax_checker, one_quote)
{
	(void)data;
	const char *input = "echo   \" missing one quote";
	ASSERT_EQUAL(ERROR, has_missing_quotes(input));
}

CTEST2(quote_syntax_checker, three_quote)
{
	(void)data;
	const char *input = "echo   \" missing \" one quote \"";
	ASSERT_EQUAL(ERROR, has_missing_quotes(input));
}

CTEST2(quote_syntax_checker, one_double_one_single_quote)
{
	(void)data;
	const char *input = "echo   \" missing one quote '";
	ASSERT_EQUAL(ERROR, has_missing_quotes(input));
}

CTEST2(quote_syntax_checker, two_pairs_of_quotes)
{
	(void)data;
	const char *input = "echo   \"missing\" \"one\" quote ";
	ASSERT_EQUAL(SUCCESS, has_missing_quotes(input));
}

CTEST2(quote_syntax_checker, no_quote)
{
	(void)data;
	const char *input = "echo   no quote ";
	ASSERT_EQUAL(SUCCESS, has_missing_quotes(input));
}


CTEST2(quote_syntax_checker, single_and_double_quote)
{
	(void)data;
	const char *input = "echo  -n test    |  cat -e \"     ";
	ASSERT_EQUAL(ERROR, has_missing_quotes(input));
}