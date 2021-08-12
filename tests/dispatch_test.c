#include "ctest.h"
#include "../src/parser/dispatcher.h"

CTEST(dispatch_test, echo_true)
{
	const char *input = "test";
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, ECHO));
}

CTEST(dispatch_test, unknown_command)
{
	const char *input = "dnjekndwejk";
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, INVALID));
}