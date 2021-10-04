#include "ctest.h"
#include <syntax/check_syntax.h>

CTEST(left_angle, valid_single_syntax)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax(" <main.c cat -e"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("cat -e      <main.c"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("cat -e < main.c "));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("> out ls"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("> out ls"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax(" >out ls"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("ls      >out"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("ls > out "));
}

CTEST(single_angled_bracket, multi_valid_files)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c < Makefile cat -e  < README.md       "));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< main.c < Makefile cat -e  < README.md >out > out2 > out3      "));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("< Makefile >out1 cat -e   >outreal      <main.c   "));
}


CTEST(single_angled_bracket, only_single_angled_bracket)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax(">"));
}

CTEST(single_angled_bracket, last_char_single_angled_bracket)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("random text here: <"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("random text here: >"));
}

// if fullfile name is digits, must be followed by space ex.
// echo  halla >1>2
// syntax error near unexpected token `1'
// echo halla >h1>2 is fine, fuckin minishell
CTEST(single_angled_bracket, numbered_outfiles_without_spaces)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo halla >1 > out"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo halla >1> out"));
}