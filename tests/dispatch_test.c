#include "ctest.h"
#include "../src/parser/dispatcher.h"

CTEST(dispatch_test, echo_true)
{
	const char *input = "echo";
	ASSERT_EQUAL(SUCCESS, dispatch_commands(&input, ECHO));
}