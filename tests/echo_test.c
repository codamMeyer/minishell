#include "ctest.h"
#include "../src/commands/commands.h"

CTEST(echo_test, returns_true_with_emptry_str_input)
{
	const char *input = "";
	ASSERT_TRUE(echo_command(&input));
}

// CTEST(echo_test, returns_true_with_emptry_str_input)
// {
// 	const char *input = "";
// 	ASSERT_TRUE(echo_command(&input));
// }

CTEST(echo_utils_test, format_string_test)
{
	const char *input = "";
	ASSERT_NOT_NULL(format_string(input));
}

CTEST(echo_utils_test, substr_len_test)
{
	const char *input = "12345|";
	ASSERT_EQUAL(5, get_substr_len(input));
}