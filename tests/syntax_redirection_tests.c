#include "ctest.h"
#include <syntax/check_syntax.h>
#include <syntax/redirection_syntax.h>
#include <syntax/write_errors.h>

CTEST(error_buffer, basics)
{
    char buffer[BUFFER_SIZE];

    append_error_token_to_buffer("<<<<<<", buffer);
    ASSERT_STR("<<", buffer);
}

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

CTEST(single_angled_bracket, numbered_outfiles_without_spaces)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo halla >1 > out"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo halla >h1> out"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo halla >1 >2e>out"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo halla >1 >2>3 >out"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo halla >1 >2 >3> out"));
}

CTEST(single_angled_bracket, with_spaces_followed_another_redirect_char)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo halla > > out"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo halla > < out"));
}

CTEST(multi_angled_brackets, valid_multi_angled_brackets)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo >> appending"));
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("<<       EOF cat -e"));
}

CTEST(multi_angled_brackets, invalid_multi_angled_brackets)
{
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo >>> NOT_appending"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<< < EOF cat -e"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo > >> NOT_appending"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<< < EOF cat -e"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax(">>1>2  cat -e main.c"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<< < EOF cat -e"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax(">><<2  cat -e main.c"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("<<>> main.c cat -e"));
}

CTEST(multi_angled_brackets, valid_diamond_brackets)
{
    ASSERT_EQUAL(TRUE, is_valid_redirection_syntax("echo <> valid"));
    ASSERT_EQUAL(FALSE, is_valid_redirection_syntax("echo <>< valid"));

}
