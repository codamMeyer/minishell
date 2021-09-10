#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "ctest.h"

CTEST_DATA(command_table_redirection_tests)
{
    t_command command_table[100];
};

CTEST_SETUP(command_table_redirection_tests)
{
    (void)data;
};

CTEST_TEARDOWN(command_table_redirection_tests)
{
    (void)data;
};

CTEST2(command_table_redirection_tests, one_command_echo)
{
    const char *input = "echo Hello you this is a test";
    ASSERT_EQUAL(1, populate_commands_table(input, data->command_table));
    ASSERT_EQUAL(ECHO, data->command_table[0].code);
    ASSERT_STR(" Hello you this is a test", data->command_table[0].arg.start);
}
