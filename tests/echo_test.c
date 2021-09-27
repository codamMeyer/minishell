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
	strncpy(&echo_buf1[0], string_to_write, len);
}

CTEST2(echo_test, empty_str)
{
	const char *input = "";
	data->command.arg.start = input;
	data->command.arg.end = input;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("\n", &echo_buf1[0]);
}

CTEST2(echo_test, simple_str_without_quotes)
{
	const char *input = "simple test string";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg.len = 18;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("simple test string\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("simple test string\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_and_with_quotes)
{
	const char *input = "     first string trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 58;
	data->command.arg.len = 58;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("first string trimmed      second string not trimmed\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_trimmed_and_with_quotes)
{
	const char *input = "     first           string             trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 80;
	data->command.arg.len = 80;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("first string trimmed      second string not trimmed\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"     first           string\"      second      string        trimmed";
	data->command.arg.start = input;
	data->command.arg.end = input + 68;
	data->command.arg.len = 68;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("     first           string second string trimmed\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("     first           string second string trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_4_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"   First  \"      string  \" N  O  T  trimmed\"      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 52;
	data->command.arg.len = 52;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("   First   string  N  O  T  trimmed !\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("   First   string  N  O  T  trimmed !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_strs_with_and_without_quotes_n_flag)
{
	const char *input = "-n \"   First  \"      string  \" N  O  T  trimmed\"      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 55;
	data->command.arg.len = 55;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("   First   string  N  O  T  trimmed !"), strlen(&echo_buf1[0]));
	ASSERT_STR("   First   string  N  O  T  trimmed !", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_empty_strings)
{
	const char *input = "    \"\"\"\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 8;
	data->command.arg.len = 8;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_without_space_in_between)
{
	const char *input = "hello\"you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 10;
	data->command.arg.len = 10;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("helloyou\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("helloyou\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between)
{
	const char *input = "hello \"you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 11;
	data->command.arg.len = 11;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello you\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between_2)
{
	const char *input = "hello\" you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 11;
	data->command.arg.len = 11;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello you\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, mmultiple_n_flags_with_spaces)
{
	const char *input = "-n -n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 15;
	data->command.arg.len = 15;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello you"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, multiple_n_flags_with_no_spacing)
{
	const char *input = "-n-n-n-n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg.len = 18;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("-n-n-n-n hello you\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("-n-n-n-n hello you\n", &echo_buf1[0]);
}


CTEST2(echo_test, n_flag_with_multiple_ns)
{
	const char *input = "-nnnnnnn hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg.len = 18;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello you"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_invalid)
{
	const char *input = "-nnnnnnn-n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 20;
	data->command.arg.len = 20;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("-nnnnnnn-n hello you\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("-nnnnnnn-n hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_valid)
{
	const char *input = "-nnnnnnn -n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 21;
	data->command.arg.len = 21;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello you"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, followed_by_pipe)
{
	(void)data;
	t_command command[100];
	const char *input = "echo hello you this is a | echo second command";
	ASSERT_EQUAL(2, populate_commands_table(input, command));
	ASSERT_EQUAL(SUCCESS, echo_command(command[0], write_to_buf));
	ASSERT_EQUAL(strlen("hello you this is a\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello you this is a\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_string_with_single_quote)
{
	const char *input = "hello    '!     you     !'";
	data->command.arg.start = input;
	data->command.arg.end = input + 26;
	data->command.arg.len = 26;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello !     you     !\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello !     you     !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_string_with_single_quote_and_var)
{
	const char *input = "hello    '$PWD'";
	data->command.arg.start = input;
	data->command.arg.end = input + 15;
	data->command.arg.len = 15;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_EQUAL(strlen("hello $PWD\n"), strlen(&echo_buf1[0]));
	ASSERT_STR("hello $PWD\n", &echo_buf1[0]);
}