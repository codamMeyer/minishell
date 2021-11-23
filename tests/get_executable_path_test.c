#include "ctest.h"
#include "../src/parser/get_executable_path.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

CTEST(test_executability, invalid_executable_path)
{
	struct stat control;
	char	*ls_cmd = "bin/l";
	char	*cat_cmd = "/sbin/cat";
	char	*grep_cmd = "/usr/bin/grep/";

	ASSERT_EQUAL(stat(ls_cmd,  &control), is_executable(ls_cmd));
	ASSERT_EQUAL(stat(cat_cmd, &control), is_executable(cat_cmd));
	ASSERT_EQUAL(stat(grep_cmd, &control), is_executable(grep_cmd));
}

CTEST(test_executability, executable_path)
{
	struct stat control;
	char	*ls_cmd = "/bin/ls";
	char	*cat_cmd = "/bin/cat";
	char	*grep_cmd = "/usr/bin/grep";

	ASSERT_EQUAL(stat(ls_cmd, &control), is_executable(ls_cmd));
	ASSERT_EQUAL(stat(cat_cmd, &control), is_executable(cat_cmd));
	ASSERT_EQUAL(stat(grep_cmd, &control), is_executable(grep_cmd));
}

CTEST(test_executability, invalid_ralative_paths)
{
	char	*ls_cmd = "ls";
	char	*cat_cmd = "cat";
	char	*grep_cmd = "grep";

	ASSERT_EQUAL(access(ls_cmd, F_OK), is_executable(ls_cmd)); 
	ASSERT_EQUAL(access(cat_cmd, F_OK), is_executable(cat_cmd)); 
	ASSERT_EQUAL(access(grep_cmd, F_OK), is_executable(grep_cmd));
}

CTEST(test_executability, ralative_paths)
{
	char	*ls_cmd = "/../../../bin/ls";
	char	*cat_cmd = "/../../../bin/cat";
	char	*grep_cmd = "/../../usr/bin/grep";

	ASSERT_EQUAL(access(ls_cmd, F_OK), is_executable(ls_cmd)); 
	ASSERT_EQUAL(access(cat_cmd, F_OK), is_executable(cat_cmd)); 
	ASSERT_EQUAL(access(grep_cmd, F_OK), is_executable(grep_cmd)); 
}

CTEST(tests_exe_path_return, null_input)
{
	ASSERT_NULL(get_executable_path(NULL));
}

CTEST(tests_exe_path_return,incomplete_command)
{
	char *ls = get_executable_path("/ls");
	char *pwd = get_executable_path("/pwd");
	ASSERT_NULL(get_executable_path("l"));
	ASSERT_STR("/ls", ls);
	ASSERT_STR("/pwd", pwd);
	free(ls);
	free(pwd);
}

CTEST(tests_exe_path_return, invalid_command)
{
	char *ls = get_executable_path("ls/");

	ASSERT_NULL(get_executable_path("ltp"));
	ASSERT_NULL(get_executable_path("###"));
	ASSERT_STR("ls/", ls);
	ASSERT_NULL(get_executable_path("      "));
	free(ls);
}
