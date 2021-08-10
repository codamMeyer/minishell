#include "ctest.h"
#include "../src/commands/commands.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
// possible strings
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string followed by pipe (|)    )
// ("")
// ( )
// (		whitespace         4 dddaaaaaayyyyyys)
// (	"	whitespace         4 dddaaaaaayyyyyys, with quotes      ")
// (	"	quotes with \"\" quotes"      ")

int size = 4096;
char buf[4096];

CTEST_DATA(echo_test)
{
};

CTEST_SETUP(echo_test)
{
	(void)data;
	bzero(&buf[0], size);
};

CTEST_TEARDOWN(echo_test)
{
	(void)data;
};

void	write_to_buf(const char *string_to_write)
{
	const int len = strlen(string_to_write);

	strncpy(&buf[0], string_to_write, len);
}

CTEST2(echo_test, empty_str)
{
	(void)data;
	const char *input = "";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("\n", &buf[0]);
}

CTEST2(echo_test, simple_str_without_quotes)
{
	(void)data;
	const char *input = "simple test string";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("simple test string\n", &buf[0]);
}

CTEST2(echo_test, write_2_strs_without_and_with_quotes)
{
	(void)data;
	const char *input = "     first string trimmed \"     second string not trimmed\"";
	const char *expected = "first string trimmed      second string not trimmed\n";
	const int expected_len = strlen(expected);
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR(expected, &buf[0]);
	ASSERT_EQUAL(expected_len, strlen(&buf[0]));
}

CTEST2(echo_test, write_2_strs_without_trimmed_and_with_quotes)
{
	(void)data;
	const char *input = "     first           string             trimmed \"     second string not trimmed\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	
	ASSERT_STR("first string trimmed      second string not trimmed\n", &buf[0]);
}

CTEST2(echo_test, write_2_strs_with_and_without_quotes_trimmed)
{
	(void)data;
	const char *input = "\"     first           string\"      second      string        trimmed";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("     first           string second string trimmed\n", &buf[0]);
}

CTEST2(echo_test, write_4_strs_with_and_without_quotes_trimmed)
{
	(void)data;
	const char *input = "\"   First  \"      string  \" N  O  T  trimmed\"      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("   First   string  N  O  T  trimmed !\n", &buf[0]);
}

CTEST2(echo_test, write_strs_with_and_without_quotes_n_flag)
{
	(void)data;
	const char *input = "-n \"   First  \"      string  \" N  O  T  trimmed\"      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("   First   string  N  O  T  trimmed !", &buf[0]);
}
      
CTEST2(echo_test, write_strs_with_missing_quote_and_without_quotes)
{
	(void)data;
	const char *input = "\"   First  string  \"        trimmed\"      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("   First  string   trimmed!\n", &buf[0]);
}

CTEST2(echo_test, write_str_missing_closing_quote)
{
	(void)data;
	const char *input = "\"   First  string         trimmed      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("First string trimmed !\n", &buf[0]);
}

CTEST2(echo_test, write_str_missing_closing_quote_at_the_end)
{
	(void)data;
	const char *input = "   First  string         trimmed      !\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("First string trimmed !\n", &buf[0]);
}

CTEST2(echo_test, write_str_double_quote_in_the_middle)
{
	(void)data;
	const char *input = "   First  string   \"      trimmed      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("First string trimmed !\n", &buf[0]);
}

CTEST2(echo_test, write_two_empty_strings)
{
	(void)data;
	const char *input = "    \"\"\"\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("\n", &buf[0]);
}

CTEST2(echo_test, write_two_strs_without_space_in_between)
{
	(void)data;
	const char *input = "hello\"you\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("helloyou\n", &buf[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between)
{
	(void)data;
	const char *input = "hello \"you\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("hello you\n", &buf[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between_2)
{
	(void)data;
	const char *input = "hello\" you\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("hello you\n", &buf[0]);
}

CTEST2(echo_test, mmultiple_n_flags_with_spaces)
{
	(void)data;
	const char *input = "-n -n hello you";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("hello you", &buf[0]);
}

CTEST2(echo_test, multiple_n_flags_with_no_spacing)
{
	(void)data;
	const char *input = "-n-n-n-n hello you";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("-n-n-n-n hello you\n", &buf[0]);
}


CTEST2(echo_test, n_flag_with_multiple_ns)
{
	(void)data;
	const char *input = "-nnnnnnn hello you";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	
	ASSERT_STR("hello you", &buf[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_invalid)
{
	(void)data;
	const char *input = "-nnnnnnn-n hello you";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("-nnnnnnn-n hello you\n", &buf[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_valid)
{
	(void)data;
	const char *input = "-nnnnnnn -n hello you";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));

	ASSERT_STR("hello you", &buf[0]);
}