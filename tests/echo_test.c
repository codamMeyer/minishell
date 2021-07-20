#include "ctest.h"
#include "../src/commands/commands.h"
#include "../libft/libft.h"

// possible strings
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string followed by pipe (|)    )
// ("")
// ( )
// (		whitespace         4 dddaaaaaayyyyyys)
// (	"	whitespace         4 dddaaaaaayyyyyys, with quotes      ")
// (	"	quotes with \"\" quotes"      ")

CTEST(echo_test, returns_true_with_emptry_str_input)
{
	const char *input = "";
	ASSERT_EQUAL(SUCCESS, echo_command(&input));
}

CTEST(echo_utils_test, format_string_test)
{
	const char *input = "";
	ASSERT_NOT_NULL(get_echo_args(&input));
}

CTEST(echo_utils_test, empty_substr_len_test)
{
	const char *input = "";
	ASSERT_EQUAL(0, get_substr_len(input));
}

CTEST(echo_utils_test, no_pipe_substr_len_test)
{
	const char *input = "nopipe";
	ASSERT_EQUAL(ft_strlen(input), get_substr_len(input));
}

CTEST(echo_utils_test, substr_len_test)
{
	const char *input = "12345|";
	ASSERT_EQUAL(5, get_substr_len(input));
}

CTEST(echo_utils_test, substr_zero_len_test)
{
	const char *input = "";
	ASSERT_EQUAL(0, get_substr_len(input));
}

CTEST(echo_utils_test, true_check_quotes)
{
	t_check_quotes quotes;
	
	has_inverted_comma_set("\"appletrreee\"", &quotes);
	ASSERT_TRUE(quotes.opening);
	ASSERT_TRUE(quotes.closing);
}

CTEST(echo_utils_test, only_opening_quotes)
{
	t_check_quotes quotes;

	has_inverted_comma_set("\"stringcheese", &quotes);
	ASSERT_TRUE(quotes.opening);
	ASSERT_FALSE(quotes.closing);
}

CTEST(echo_utils_test, check_no_quotes)
{
	t_check_quotes quotes;

	has_inverted_comma_set("hala@me", &quotes);
	ASSERT_FALSE(quotes.opening);
	ASSERT_FALSE(quotes.closing);
}

CTEST(echo_utils_test, format_quotes_string)
{
	char **split_splat = format_string_with_quotes("\"look      at me \"now heeeey\"\"");
	
	ASSERT_NULL(split_splat[1]);
	ASSERT_STR("look      at me \"now heeeey", split_splat[0]);
}

CTEST(echo_utils_test, format_no_quotes_string)
{
	char *args = "    No     quotes, whitespace    should   be    removed   ";
	char **formatted_args = format_echo_args(args);

	ASSERT_STR("No", formatted_args[0]);
	ASSERT_STR("quotes,", formatted_args[1]);
	ASSERT_STR("whitespace", formatted_args[2]);
	ASSERT_STR("should", formatted_args[3]);
	ASSERT_STR("be", formatted_args[4]);
	ASSERT_STR("removed", formatted_args[5]);
	ASSERT_NULL(formatted_args[6]);
}

CTEST(echo_utils_test, echo_w_n_flag)
{
	const char *input = "    -n hello";
	ASSERT_TRUE(parse_n_flag(&input));
	ASSERT_STR(" hello", input);
}

CTEST(echo_utils_test, echo_w_n_flag_after_quote)
{
	const char *input = "   \" -n hello \"";
	ASSERT_FALSE(parse_n_flag(&input));
}

// CTEST(echo_utils_test, format_string_w_quotes_and_whitespace)
// {
// 	char *str = "    \"     No     quotes   \"";
// 	char **m_str = parse_echo(((const char **)(&str)));

// 	ASSERT_STR("     No", m_str[0]);
// 	ASSERT_STR("quotes   ", m_str[1]);
// 	ASSERT_NULL(m_str[2]);
// }