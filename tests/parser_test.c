#include "ctest.h"
#include "../srcs/parser/parser.h"

// assumed commands echo pwd
// use run for testability
// 

CTEST(parser, parser_success_return)
{
    ASSERT_TRUE(parser());
}
