#include "ctest.h"
#include <syntax/check_syntax.h>

CTEST(pipes, no_pipe)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo"));
}


CTEST(pipes, valid_pipe)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo | cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo| cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo |cat -e"));
}

CTEST(pipes, valid_multi_pipes)
{
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo | cat -e | wc"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo |cat -e| wc"));
    ASSERT_EQUAL(TRUE, is_valid_syntax("echo hallo| cat -e |wc"));
}

CTEST(pipes, only_pipe)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("|"));
}

CTEST(pipes, invalid_first_char_pipe)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("| echo hallo"));
}

CTEST(pipes, invalid_last_char_pipe)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo|"));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo     |"));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo | "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo | cat -e | wc -l |"));
}

CTEST(pipes, invalid_last_char_pipe_with_spaces)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      |           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo|           "));
}

CTEST(pipes, double_pipes)
{
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      || cat -e           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      | | cat -e           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      |       | cat -e           "));
    ASSERT_EQUAL(FALSE, is_valid_syntax("echo hallo      |        cat -e    | | "));
}
