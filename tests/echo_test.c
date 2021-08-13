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
	data->command.arg_len = 18;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("simple test string\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_and_with_quotes)
{
	const char *input = "     first string trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 60;
	data->command.arg_len = 60;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_trimmed_and_with_quotes)
{
	const char *input = "     first           string             trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 82;
	data->command.arg_len = 82;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"     first           string\"      second      string        trimmed";
	data->command.arg.start = input;
	data->command.arg.end = input + 70;
	data->command.arg_len = 70;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("     first           string second string trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_4_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"   First  \"      string  \" N  O  T  trimmed\"      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 56;
	data->command.arg_len = 56;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("   First   string  N  O  T  trimmed !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_strs_with_and_without_quotes_n_flag)
{
	const char *input = "-n \"   First  \"      string  \" N  O  T  trimmed\"      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 59;
	data->command.arg_len = 59;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("   First   string  N  O  T  trimmed !", &echo_buf1[0]);
}
      
CTEST2(echo_test, write_strs_with_missing_quote_and_without_quotes)
{
	const char *input = "\"   First  string  \"        trimmed\"      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 46;
	data->command.arg_len = 46;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("   First  string   trimmed!\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_str_missing_closing_quote)
{
	const char *input = "\"   First  string         trimmed      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 41;
	data->command.arg_len = 41;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_str_missing_closing_quote_at_the_end)
{
	const char *input = "   First  string         trimmed      !\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 41;
	data->command.arg_len = 41;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_str_double_quote_in_the_middle)
{
	const char *input = "   First  string   \"      trimmed      !";
	data->command.arg.start = input;
	data->command.arg.end = input + 41;
	data->command.arg_len = 41;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_empty_strings)
{
	const char *input = "    \"\"\"\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 13;
	data->command.arg_len = 13;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_without_space_in_between)
{
	const char *input = "hello\"you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 12;
	data->command.arg_len = 12;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("helloyou\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between)
{
	const char *input = "hello \"you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 13;
	data->command.arg_len = 13;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_two_strs_with_space_in_between_2)
{
	const char *input = "hello\" you\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 13;
	data->command.arg_len = 13;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, mmultiple_n_flags_with_spaces)
{
	const char *input = "-n -n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 15;
	data->command.arg_len = 15;
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, multiple_n_flags_with_no_spacing)
{
	const char *input = "-n-n-n-n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg_len = 18;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("-n-n-n-n hello you\n", &echo_buf1[0]);
}


CTEST2(echo_test, n_flag_with_multiple_ns)
{
	const char *input = "-nnnnnnn hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg_len = 18;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_invalid)
{
	const char *input = "-nnnnnnn-n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 20;
	data->command.arg_len = 20;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("-nnnnnnn-n hello you\n", &echo_buf1[0]);
}

CTEST2(echo_test, n_flag_with_multiple_ns_valid)
{
	const char *input = "-nnnnnnn -n hello you";
	data->command.arg.start = input;
	data->command.arg.end = input + 21;
	data->command.arg_len = 21;		
	ASSERT_EQUAL(SUCCESS, echo_command(data->command, write_to_buf));
	ASSERT_STR("hello you", &echo_buf1[0]);
}

CTEST2(echo_test, followed_by_pipe)
{
	(void)data;
	const char *input = "echo hello you this is a |";
	t_command *command = get_commands(&input);
	ASSERT_EQUAL(SUCCESS, echo_command(command[0], write_to_buf));
	ASSERT_STR("hello you this is a \n", &echo_buf1[0]);
	free(command);
}