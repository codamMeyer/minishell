#include "ctest.h"
#include "../src/parser/parser.h"

CTEST(parse_input, success_return)
{
    ASSERT_TRUE(parse_input("echo "));
}

CTEST(parse_input, no_line_to_parse)
{
    ASSERT_FALSE(parse_input(NULL));
}

CTEST(parse_command, invalid_command)
{
    const char *input = "ecth";
    ASSERT_EQUAL(INVALID, parse_command(&input));
}

CTEST(parse_command, invalid_echo_command)
{
    const char *input = "echos";
    ASSERT_EQUAL(INVALID, parse_command(&input));
}

CTEST(parse_command, echo_command)
{
    const char *input = "echo";
    ASSERT_EQUAL(ECHO, parse_command(&input));
}

CTEST(parse_command, echo_command_with_arg)
{
    const char *input = "echo hello";
    ASSERT_EQUAL(ECHO, parse_command(&input));
    ASSERT_STR(" hello", input);
}

CTEST(parse_command, echo_command_with_spaces_before)
{
    const char *input = "      echo hello";
    ASSERT_EQUAL(ECHO, parse_command(&input));
    ASSERT_STR(" hello", input);
}

CTEST(parse_command, only_spaces)
{
    const char *only_spaces = "                          ";
    ASSERT_EQUAL(EMPTY_LINE, parse_command(&only_spaces));
    const char *empty = "";
    ASSERT_EQUAL(EMPTY_LINE, parse_command(&empty));
}

CTEST(parse_command, pwd_command)
{
    const char *pwd_command = "pwd";
    ASSERT_EQUAL(PWD, parse_command(&pwd_command));
}

CTEST(parse_command, pwd_command_with_spaces_before)
{
    const char *pwd_command = "            pwd";
    ASSERT_EQUAL(PWD, parse_command(&pwd_command));
}

CTEST(parse_command, pwd_command_with_spaces_after)
{
    const char *pwd_command = "pwd            ";
    ASSERT_EQUAL(PWD, parse_command(&pwd_command));
}

CTEST(parse_command, pwd_command_almost_correct)
{
    const char *pwd_command = "pwdd";
    ASSERT_EQUAL(INVALID, parse_command(&pwd_command));
}