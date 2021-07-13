#include "ctest.h"
#include "../srcs/parser/parser.h"

// assumed commands echo pwd
// use run for testability

CTEST(parse_input, success_return)
{
    ASSERT_TRUE(parse_input("test"));
}

CTEST(parse_input, no_line_to_parse)
{
    ASSERT_FALSE(parse_input(NULL));
}

CTEST(parse_input, valid_input)
{
    ASSERT_TRUE(parse_input("test"));
}
