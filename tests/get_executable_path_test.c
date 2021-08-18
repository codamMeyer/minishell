#include "ctest.h"
#include "../src/parser/get_executable_path.h"

CTEST(tests_exe_path_return, null_input)
{
	ASSERT_NULL(get_executable_path(NULL));
}

// CTEST(tests_exe_path_return,incomplete_path)
// {
// 	ASSERT_NULL(get_executable_path("ls"));
// 	// ASSERT_NULL(get_executable_path("      /ls"));
// 	// ASSERT_NULL(get_executable_path("     /pwd"));
// }

CTEST(tests_exe_path_return, path_for_valid_commands)
{
	ASSERT_STR("/bin/ls", get_executable_path("/ls"));
	ASSERT_STR("/bin/cat", get_executable_path("/cat"));
	ASSERT_STR("/usr/bin/grep", get_executable_path("/grep"));
}
