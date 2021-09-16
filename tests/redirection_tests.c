#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "ctest.h"

#define BUFFERSIZE 1024

CTEST(spaces_test, empty_str)
{
    ASSERT_EQUAL(0, count_consecutive_spaces(""));
}

CTEST(spaces_test, spaced_str)
{
    ASSERT_EQUAL(4, count_consecutive_spaces("    "));
    ASSERT_EQUAL(4, count_consecutive_spaces("    cmd"));

}

CTEST(file_name_tests, basic_file_name)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "test_file";
    ASSERT_EQUAL(ft_strlen(&file_name[0]), get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR(file_name, buffer);
}

CTEST(file_name_tests, file_name_with_spaces)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "\"      test_file      \"";
    ASSERT_EQUAL(ft_strlen(&file_name[0]), get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("      test_file      ", buffer);
}

CTEST(file_name_tests, file_name_with_next_command)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "test_file | applesauces";
    ASSERT_EQUAL(9, get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("test_file", buffer);
}

CTEST(file_name_tests, file_name_with_spaces_and_quotes)
{
    char buffer[BUFFERSIZE];
    char file_name[] = "\"      test_file\"| applesauces";
    ASSERT_EQUAL(ft_strlen("      test_file") + 2, get_file_name_and_length(&buffer[0], file_name));
    ASSERT_STR("      test_file", buffer);
}