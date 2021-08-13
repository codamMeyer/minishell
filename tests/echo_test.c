#include "ctest.h"
#include "../src/commands/commands.h"
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
	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
	ASSERT_STR("\n", &echo_buf1[0]);
}

CTEST2(echo_test, simple_str_without_quotes)
{
	const char *input = "simple test string";
	data->command.arg.start = input;
	data->command.arg.end = input + 18;
	data->command.arg_len = 18;
	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
	ASSERT_STR("simple test string\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_and_with_quotes)
{
	const char *input = "     first string trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 60;
	data->command.arg_len = 60;
	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_without_trimmed_and_with_quotes)
{
	const char *input = "     first           string             trimmed \"     second string not trimmed\"";
	data->command.arg.start = input;
	data->command.arg.end = input + 82;
	data->command.arg_len = 82;
	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &echo_buf1[0]);
}

CTEST2(echo_test, write_2_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"     first           string\"      second      string        trimmed";
	data->command.arg.start = input;
	data->command.arg.end = input + 70;
	data->command.arg_len = 70;
	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
	ASSERT_STR("     first           string second string trimmed\n", &echo_buf1[0]);
}

// CTEST2(echo_test, write_4_strs_with_and_without_quotes_trimmed)
// {
// 	data->command.input = ft_strdup("\"   First  \"      string  \" N  O  T  trimmed\"      !");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("   First   string  N  O  T  trimmed !\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_strs_with_and_without_quotes_n_flag)
// {
// 	data->command.input = ft_strdup("-n \"   First  \"      string  \" N  O  T  trimmed\"      !");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("   First   string  N  O  T  trimmed !", &echo_buf1[0]);
// }
      
// CTEST2(echo_test, write_strs_with_missing_quote_and_without_quotes)
// {
// 	data->command.input = ft_strdup("\"   First  string  \"        trimmed\"      !");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("   First  string   trimmed!\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_str_missing_closing_quote)
// {
// 	data->command.input = ft_strdup("\"   First  string         trimmed      !");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_str_missing_closing_quote_at_the_end)
// {
// 	data->command.input = ft_strdup("   First  string         trimmed      !\"");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_str_double_quote_in_the_middle)
// {
// 	data->command.input = ft_strdup("   First  string   \"      trimmed      !");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("First string trimmed !\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_two_empty_strings)
// {
// 	data->command.input = ft_strdup("    \"\"\"\"");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_two_strs_without_space_in_between)
// {
// 	data->command.input = ft_strdup("hello\"you\"");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("helloyou\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_two_strs_with_space_in_between)
// {
// 	data->command.input = ft_strdup("hello \"you\"");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("hello you\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, write_two_strs_with_space_in_between_2)
// {
// 	data->command.input = ft_strdup("hello\" you\"");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("hello you\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, mmultiple_n_flags_with_spaces)
// {
// 	data->command.input = ft_strdup("-n -n hello you");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("hello you", &echo_buf1[0]);
// }

// CTEST2(echo_test, multiple_n_flags_with_no_spacing)
// {
// 	data->command.input = ft_strdup("-n-n-n-n hello you");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("-n-n-n-n hello you\n", &echo_buf1[0]);
// }


// CTEST2(echo_test, n_flag_with_multiple_ns)
// {
// 	data->command.input = ft_strdup("-nnnnnnn hello you");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("hello you", &echo_buf1[0]);
// }

// CTEST2(echo_test, n_flag_with_multiple_ns_invalid)
// {
// 	data->command.input = ft_strdup("-nnnnnnn-n hello you");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("-nnnnnnn-n hello you\n", &echo_buf1[0]);
// }

// CTEST2(echo_test, n_flag_with_multiple_ns_valid)
// {
// 	data->command.input = ft_strdup("-nnnnnnn -n hello you");
// 	ASSERT_EQUAL(SUCCESS, echo_command(&data->command, write_to_buf));
// 	ASSERT_STR("hello you", &echo_buf1[0]);
// }