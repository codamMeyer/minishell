#include "ctest.h"
#include "../srcs/parser/parser.h"

// assumed commands echo pwd
// use run for testability

CTEST(parse_input, success_return)
{
    ASSERT_TRUE(parse_input(ECHO_STR));
}

CTEST(parse_input, no_line_to_parse)
{
    ASSERT_FALSE(parse_input(NULL));
}

CTEST(get_command, invalid_command)
{
    ASSERT_EQUAL(INVALID, get_command("ecth"));
}