#include "ctest.h"
#include "../src/commands/commands.h"
#include "../libft/libft.h"
#include <stdio.h>
// possible strings
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string followed by pipe (|)    )
// ("")
// ( )
// (		whitespace         4 dddaaaaaayyyyyys)
// (	"	whitespace         4 dddaaaaaayyyyyys, with quotes      ")
// (	"	quotes with \"\" quotes"      ")


void	write_empty_str(const char *string_to_write, int len)
{
	(void)len;
	ASSERT_STR("\n", string_to_write);
}

CTEST(echo_test, empty_str)
{
	const char *input = "";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_empty_str));
}

void	write_str_without_quotes(const char *string_to_write, int len)
{
	(void)len;
	ASSERT_STR("simple test string\n", string_to_write);
}

CTEST(echo_test, simple_str_without_quotes)
{
	const char *input = "simple test string";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_str_without_quotes));
}

void	write_2_strs_without_and_with_quotes(const char *string_to_write, int len)
{
	(void)len;
	const char *str = {"first string trimmed      second string not trimmed\n"};
	ASSERT_STR(str, string_to_write);
}

CTEST(echo_test, write_2_strs_without_and_with_quotes)
{
	const char *input = "     first string trimmed \"     second string not trimmed\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_2_strs_without_and_with_quotes));
}

void	write_2_strs_without_trimmed_and_with_quotes(const char *string_to_write, int len)
{
	(void)len;
	const char *str = {"first string trimmed      second string not trimmed\n"};
	ASSERT_STR(str, string_to_write);
}

CTEST(echo_test, write_2_strs_without_trimmed_and_with_quotes)
{
	const char *input = "     first           string             trimmed \"     second string not trimmed\"";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_2_strs_without_trimmed_and_with_quotes));
}

void	write_2_strs_with_and_without_quotes_trimmed(const char *string_to_write, int len)
{
	(void)len;
	const char *str = {"     first           string second string trimmed\n"};
	ASSERT_STR(str, string_to_write);
}

CTEST(echo_test, write_2_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"     first           string\"      second      string        trimmed";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_2_strs_with_and_without_quotes_trimmed));
}

void	write_4_strs_with_and_without_quotes_trimmed(const char *string_to_write, int len)
{
	(void)len;
	const char *str = {"   First   string  N  O  T  trimmed !\n"};
	ASSERT_STR(str, string_to_write);
}

CTEST(echo_test, write_4_strs_with_and_without_quotes_trimmed)
{
	const char *input = "\"   First  \"      string  \" N  O  T  trimmed\"      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_4_strs_with_and_without_quotes_trimmed));
}

void	write_strs_with_and_without_quotes_n_flag(const char *string_to_write, int len)
{
	(void)len;
	const char *str = {"   First   string  N  O  T  trimmed !"};
	ASSERT_STR(str, string_to_write);
}

CTEST(echo_test, write_strs_with_and_without_quotes_n_flag)
{
	const char *input = "-n \"   First  \"      string  \" N  O  T  trimmed\"      !";
	ASSERT_EQUAL(SUCCESS, echo_command(&input, write_strs_with_and_without_quotes_n_flag));
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

