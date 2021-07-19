#include <ctest.h>
#include "../src/commands/commands.h"

CTEST(echo_test, returns_true_with_emptry_str_input)
{
	ASSERT_TRUE(echo_command(""));
}

CTEST(echo_test, returns_true_with_emptry_str_input)
{
	ASSERT_TRUE(echo_command(""));
}