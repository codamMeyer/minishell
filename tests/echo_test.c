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
	ASSERT_NOT_NULL(parse_echo(&input));
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
	char *str = "    No     quotes, whitespace    should   be    removed   ";
	char **m_str = parse_echo(((const char **)(&str)));

	ASSERT_STR("No", m_str[0]);
	ASSERT_STR("quotes,", m_str[1]);
	ASSERT_STR("whitespace", m_str[2]);
	ASSERT_STR("should", m_str[3]);
	ASSERT_STR("be", m_str[4]);
	ASSERT_STR("removed", m_str[5]);
	ASSERT_NULL(m_str[6]);
}

// CTEST(echo_utils_test, format_string_w_quotes_and_whitespace)
// {
// 	char *str = "    \"     No     quotes   \"";
// 	char **m_str = parse_echo(((const char **)(&str)));

// 	ASSERT_STR("     No", m_str[0]);
// 	ASSERT_STR("quotes   ", m_str[1]);
// 	ASSERT_NULL(m_str[2]);
// }