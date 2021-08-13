#include "ctest.h"
#include "../src/parser/parser.h"
#include <stdlib.h>

CTEST(parse_input, success_return)
{
    ASSERT_TRUE(parse_input("echo "));
}

CTEST(parse_input, no_line_to_parse)
{
    ASSERT_FALSE(parse_input(NULL));
}

CTEST(parse_command, unknown_command)
{
    const char *input = "ecth";
    ASSERT_EQUAL(INVALID, get_command_code(&input));
}

CTEST(parse_command, invalid_echo_command)
{
    const char *input = "echos";
    ASSERT_EQUAL(INVALID, get_command_code(&input));
}

CTEST(parse_command, echo_command)
{
    const char *input = "echo";
    ASSERT_EQUAL(ECHO, get_command_code(&input));
}

CTEST(parse_command, echo_command_with_arg)
{
    const char *input = "echo hello";
    ASSERT_EQUAL(ECHO, get_command_code(&input));
    ASSERT_STR(" hello", input);
}

CTEST(parse_command, echo_command_with_spaces_before)
{
    const char *input = "      echo hello";
    ASSERT_EQUAL(ECHO, get_command_code(&input));
    ASSERT_STR(" hello", input);
}

CTEST(parse_command, only_spaces)
{
    const char *only_spaces = "                          ";
    ASSERT_EQUAL(EMPTY_LINE, get_command_code(&only_spaces));
    const char *empty = "";
    ASSERT_EQUAL(EMPTY_LINE, get_command_code(&empty));
}

CTEST(parse_command, pwd_command)
{
    const char *pwd_command = "pwd";
    ASSERT_EQUAL(PWD, get_command_code(&pwd_command));
}

CTEST(parse_command, pwd_command_with_spaces_before)
{
    const char *pwd_command = "            pwd";
    ASSERT_EQUAL(PWD, get_command_code(&pwd_command));
}

CTEST(parse_command, pwd_command_with_spaces_after)
{
    const char *pwd_command = "pwd            ";
    ASSERT_EQUAL(PWD, get_command_code(&pwd_command));
}

CTEST(parse_command, pwd_command_almost_correct)
{
    const char *pwd_command = "pwdd";
    ASSERT_EQUAL(INVALID, get_command_code(&pwd_command));
}

CTEST_DATA(command_table)
{
    t_command *command_table;
};

CTEST_SETUP(command_table)
{
    data->command_table = NULL;
};

CTEST_TEARDOWN(command_table)
{
    free(data->command_table);
};

CTEST2(command_table, one_command_echo)
{
    const char *input = "echo Hello you this is a test";
    data->command_table = get_commands(&input);
    ASSERT_EQUAL(ECHO, data->command_table[0].code);
    ASSERT_STR(" Hello you this is a test", data->command_table[0].arg.start);
}

CTEST2(command_table, one_command_pwd)
{
    const char *input = "pwd arguments are irrelevant for this test";
    data->command_table = get_commands(&input);
    ASSERT_EQUAL(PWD, data->command_table[0].code);
    ASSERT_STR(" arguments are irrelevant for this test", data->command_table[0].arg.start);
}