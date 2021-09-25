#include "ctest.h"
#include <syntax/check_syntax.h>

CTEST(PIPES, VALID_PIPE)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo | cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo| cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo |cat -e"));
}

CTEST(PIPES, VALID_MULTI_PIPES)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo | cat -e | wc"));
}

CTEST(PIPES, INVALID_PIPE_FIRST_CHAR)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("| echo hallo"));
    ASSERT_EQUAL(FALSE, is_valid_syntax("      | echo hallo"));
}

CTEST(PIPES, INVALID_PIPE_LAST_CHAR)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo|"));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo     |"));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo | "));
}

CTEST(PIPES, INVALID_PIPE_LAST_CHAR_BEFORE_WHITESPACE)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      |           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo|           "));
}

CTEST(PIPES, DOUBLE_PIPES)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      || cat -e           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      | | cat -e           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      |       | cat -e           "));
}