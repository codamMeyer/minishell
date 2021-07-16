#include "ctest.h"
#include "../src/parser/dispatcher.h"

CTEST(dispatch_test, returns_false)
{
	const char *input = "exit";
	ASSERT_FALSE(dispatch_commands(&input, ECHO));
}