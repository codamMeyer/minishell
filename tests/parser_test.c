#include "ctest.h"
#include "../src/parser/command_table.h"
#include "../src/parser/parser.h"
#include <stdlib.h>
#include "arguments.h"

CTEST(parse_input, success_return)
{
    ASSERT_TRUE(parse_input("echo "));
}

CTEST(parse_input, no_line_to_parse)
{
    ASSERT_TRUE(parse_input(NULL));
}

CTEST(parse_command, unknown_command)
{
    char *input = "ecth";
    ASSERT_EQUAL(INVALID, get_command_code(input, NULL));
}

CTEST(parse_command, invalid_echo_command)
{
    char *input = "echos";
    ASSERT_EQUAL(INVALID, get_command_code(input, NULL));
}

CTEST(parse_command, echo_command)
{
    char *input = "echo";
    ASSERT_EQUAL(ECHO, get_command_code(input, NULL));
}

CTEST(parse_command, echo_command_with_arg)
{
    char *input = "echo";
    ASSERT_EQUAL(ECHO, get_command_code(input, NULL));
}

CTEST(parse_command, empty_line)
{
    char *empty_line = "";
    ASSERT_EQUAL(EMPTY_LINE, get_command_code(empty_line, NULL));
}

CTEST(parse_command, pwd_command)
{
    char *pwd_command = "pwd";
    ASSERT_EQUAL(PWD, get_command_code(pwd_command, NULL));
}

CTEST(parse_command, pwd_command_with_spaces_before)
{
    char *pwd_command = "pwd";
    ASSERT_EQUAL(PWD, get_command_code(pwd_command, NULL));
}

CTEST(parse_command, pwd_command_with_spaces_after)
{
    char *pwd_command = "pwd";
    ASSERT_EQUAL(PWD, get_command_code(pwd_command, NULL));
}

CTEST(parse_command, pwd_command_almost_correct)
{
    char *pwd_command = "pwdd";
    ASSERT_EQUAL(INVALID, get_command_code(pwd_command, NULL));
}

CTEST_DATA(command_table)
{
    t_command command_table[100];
};

CTEST_SETUP(command_table)
{
    for (int i = 0; i < 100; ++i)
    {
        data->command_table[i].arguments = NULL;
    }
};

CTEST_TEARDOWN(command_table)
{
    for (int i = 0; i < 100; ++i)
    {
        destroy_split_arg(data->command_table[i].arguments);
    }
};

CTEST2(command_table, one_command_echo)
{
    char *input = "echo Hello you this is a test";
    ASSERT_EQUAL(1, populate_commands_table(input, data->command_table));
    ASSERT_EQUAL(ECHO, data->command_table[0].code);
    ASSERT_STR("echo", data->command_table[0].arguments[0]);
    ASSERT_STR("Hello", data->command_table[0].arguments[1]);
    ASSERT_STR("you", data->command_table[0].arguments[2]);
    ASSERT_STR("this", data->command_table[0].arguments[3]);
    ASSERT_STR("is", data->command_table[0].arguments[4]);
    ASSERT_STR("a", data->command_table[0].arguments[5]);
    ASSERT_STR("test", data->command_table[0].arguments[6]);
    ASSERT_NULL(data->command_table[0].arguments[7]);

}

CTEST2(command_table, one_command_pwd)
{
    char *input = "pwd arguments are irrelevant";
    ASSERT_EQUAL(1, populate_commands_table(input, data->command_table));
    ASSERT_EQUAL(PWD, data->command_table[0].code);
}

// CTEST2(command_table, command_separated_by_pipe)
// {
//     char *input = "echo this is the end | echo test";
//     ASSERT_EQUAL(2, populate_commands_table(input, data->command_table));
//     ASSERT_EQUAL(ECHO, data->command_table[0].code);
//     ASSERT_STR("this is the end | echo test", data->command_table[0].arg.start);
//     ASSERT_STR("| echo test", data->command_table[0].arg.end);
//     ASSERT_EQUAL(ECHO, data->command_table[1].code);
//     ASSERT_STR("test", data->command_table[1].arg.start);
//     ASSERT_STR("", data->command_table[1].arg.end);
// }

// CTEST2(command_table, separate_by_pipe_and_followed_by_command_containing_quotes)
// {
//     char *input = "echo this is the end | pwd with arg";
//     ASSERT_EQUAL(2, populate_commands_table(input, data->command_table));
//     ASSERT_EQUAL(ECHO, data->command_table[0].code);
//     ASSERT_STR("this is the end | pwd with arg", data->command_table[0].arg.start);
//     ASSERT_STR("| pwd with arg", data->command_table[0].arg.end);
//     ASSERT_EQUAL(PWD, data->command_table[1].code);
//     ASSERT_STR("with arg", data->command_table[1].arg.start);
//     ASSERT_STR("", data->command_table[1].arg.end);
// }

// CTEST2(command_table, separate_by_pipe_without_quotes)
// {
//     char *input = "echo this is the end|pwd with arg";
//     ASSERT_EQUAL(2, populate_commands_table(input, data->command_table));
//     ASSERT_EQUAL(ECHO, data->command_table[0].code);
//     ASSERT_STR("this is the end|pwd with arg", data->command_table[0].arg.start);
//     ASSERT_STR("|pwd with arg", data->command_table[0].arg.end);
//     ASSERT_EQUAL(PWD, data->command_table[1].code);
//     ASSERT_STR("with arg", data->command_table[1].arg.start);
//     ASSERT_STR("", data->command_table[1].arg.end);
// }

// CTEST(quotes_test, is_between_quotes_without_quotes)
// {
//     char *input = "this test should return false |    right?";
//     ASSERT_FALSE(is_between_quotes(input, 30));
// }

// CTEST(quotes_test, is_between_quotes_with_quotes)
// {
//     char *input = "this test should \"return\" false |    right?";
//     ASSERT_FALSE(is_between_quotes(input, 32));
// }

// CTEST(quotes_test, is_between_quotes_with_more_than_one_pair_of_quotes)
// {
//     char *input = "this test should \"return\" false | \"   right \"?";
//     ASSERT_FALSE(is_between_quotes(input, 32));
// }

// CTEST(quotes_test, is_between_quotes)
// {
//     char *input = "this test should \"return true | \"   right?";
//     ASSERT_TRUE(is_between_quotes(input, 30));
// }