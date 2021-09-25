#include "ctest.h"
#include <syntax/check_syntax.h>

CTEST(PIPES, VALID_PIPE)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo | cat -e"));
}

CTEST(PIPES, INVALID_PIPE)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("| echo hallo"));
}