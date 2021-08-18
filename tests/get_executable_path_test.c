#include "ctest.h"
#include "../src/parser/get_executable_path.h"

CTEST(tests_exe_path_return, null_input)
{
	ASSERT_NULL(get_executable_path(NULL));
}

CTEST(tests_exe_path_return, path_for_ls)
{
	ASSERT_STR("/bin/ls", get_executable_path("/ls"));
}