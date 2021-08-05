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

void	write_to_buf(const char *string_to_write, int len)
{
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
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("first string trimmed      second string not trimmed\n", &buf[0]);
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

CTEST2_SKIP(echo_test, write_two_empty_strings)
{
	(void)data;
	const char *input = "    \"\"\"\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_to_buf));
	ASSERT_STR("\n", &buf[0]);
}





// CTEST(echo_utils_test, empty_substr_len_test)
// {
// 	const char *input = "";
// 	ASSERT_EQUAL(0, get_substr_len(input));
// }

// CTEST(echo_utils_test, no_pipe_substr_len_test)
// {
// 	const char *input = "nopipe";
// 	ASSERT_EQUAL(ft_strlen(input), get_substr_len(input));
// }

// CTEST(echo_utils_test, substr_len_test)
// {
// 	const char *input = "12345|";
// 	ASSERT_EQUAL(5, get_substr_len(input));
// }

// CTEST(echo_utils_test, substr_zero_len_test)
// {
// 	const char *input = "";
// 	ASSERT_EQUAL(0, get_substr_len(input));
// }

// CTEST(echo_utils_test, true_check_quotes)
// {
// 	t_check_quotes quotes;
	
// 	has_double_quotes_set("\"appletrreee\"", &quotes);
// 	ASSERT_TRUE(quotes.opening);
// 	ASSERT_TRUE(quotes.closing);
// }

// CTEST(echo_utils_test, only_opening_quotes)
// {
// 	t_check_quotes quotes;

// 	has_double_quotes_set("\"stringcheese", &quotes);
// 	ASSERT_TRUE(quotes.opening);
// 	ASSERT_FALSE(quotes.closing);
// }

// CTEST(echo_utils_test, check_no_quotes)
// {
// 	t_check_quotes quotes;

// 	has_double_quotes_set("hala@me", &quotes);
// 	ASSERT_FALSE(quotes.opening);
// 	ASSERT_FALSE(quotes.closing);
// }

// CTEST(echo_utils_test, format_quotes_string)
// {
// 	char **split_splat = format_string_with_quotes("\"look      at me \"now heeeey\"\"");

// 	ASSERT_NULL(split_splat[1]);
// 	ASSERT_STR("look      at me \"now heeeey", split_splat[0]);
// }

// CTEST(echo_utils_test, format_no_quotes_string)
// {
// 	char *args = "    No     quotes, whitespace    should   be    removed   ";
// 	char **formatted_args = format_echo_args(args);

// 	ASSERT_STR("No", formatted_args[0]);
// 	ASSERT_STR("quotes,", formatted_args[1]);
// 	ASSERT_STR("whitespace", formatted_args[2]);
// 	ASSERT_STR("should", formatted_args[3]);
// 	ASSERT_STR("be", formatted_args[4]);
// 	ASSERT_STR("removed", formatted_args[5]);
// 	ASSERT_NULL(formatted_args[6]);
// }

// CTEST(echo_utils_test, echo_w_n_flag)
// {
// 	const char *input = "    -n hello";
// 	ASSERT_TRUE(parse_n_flag(&input));
// 	ASSERT_STR(" hello", input);
// }

// CTEST(echo_utils_test, echo_w_n_flag_after_quote)
// {
// 	const char *input = "   \" -n hello \"";
// 	ASSERT_FALSE(parse_n_flag(&input));
// }

// CTEST(echo_utils_test, format_string_w_quotes_and_whitespace)
// {
// 	char *str = "    \"     No     quotes   \"";
// 	char **m_str = format_echo_args(str);

// 	ASSERT_STR("     No", m_str[0]);
// 	ASSERT_STR("quotes   ", m_str[1]);
// 	ASSERT_NULL(m_str[2]);
// }

// CTEST(echo_utils_test, format_echo_three_strings)
// {
// 	char *str = "\"     first string\"       :second str:      \"       third string \"";
// 	char **m_str = format_echo_args(str);

// 	ASSERT_STR("     first string", m_str[0]);
// 	ASSERT_STR("string", m_str[1]);
// 	ASSERT_STR(":second", m_str[2]);
// 	ASSERT_STR("str:", m_str[2]);
// 	ASSERT_STR("       third", m_str[3]);
// 	ASSERT_STR("string", m_str[4]);
// 	ASSERT_NULL(m_str[5]);
// }

