#include "ctest.h"
#include "../srcs/parser/dispatcher.h"

CTEST(dispatch_test, returns_true)
{
	const char *input = "exit";
	ASSERT_TRUE(dispatch_commands(&input, EXIT));
}