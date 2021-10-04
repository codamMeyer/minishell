#include "ctest.h"
#include <syntax/check_syntax.h>

CTEST(left_angle, single_valid_infile_syntax)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax(" <main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("cat -e      <main.c"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("cat -e < main.c "));
}

CTEST(left_angle, multi_valid_infile)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c < Makefile cat -e  < README.md       "));
}


CTEST(left_angle, only_left_angle)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<"));
}

CTEST(left_angle, last_char_left_angle)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("random text here: <"));
}

// CTEST(left_angle, last_char_left_angle)
// {
//     ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("random text here: <"));
// }