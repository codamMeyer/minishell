#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#include "env/env_for_exec.h"
#include <stdio.h>
#include <string.h>

CTEST_DATA(env_to_execve)
{
    t_env *env;
    char *export_arguments[7];
    char *unset_arguments[3];
};

CTEST_SETUP(env_to_execve)
{
    data->env = get_environment();
    data->export_arguments[0] = "export";
    data->export_arguments[1] = "banana=0";
    data->export_arguments[2] = "cheese=1";
    data->export_arguments[3] = "apple=2";
    data->export_arguments[4] = "pear=3";
    data->export_arguments[5] = "a=4";
    data->export_arguments[6] = NULL;

    data->unset_arguments[0] = "unset";
    data->unset_arguments[1] = "cheese";
    data->unset_arguments[2] = NULL;
};

CTEST_TEARDOWN(env_to_execve)
{
    destroy_env(data->env, ENV_SIZE);
};

CTEST2(env_to_execve, env_to_execve)
{
    export(data->env, data->export_arguments);
    unset(get_environment(), data->unset_arguments);
    
    char *key_ptr[BUFFER_SIZE] = {};
    char *expected[BUFFER_SIZE] = {"banana=0", "apple=2", "pear=3", "a=4"};

    env_to_char_pointer_array(key_ptr);

    ASSERT_STR(expected[0], key_ptr[0]);
    ASSERT_STR(expected[1], key_ptr[1]);
    ASSERT_STR(expected[2], key_ptr[2]);
    ASSERT_STR(expected[3], key_ptr[3]);
    ASSERT_NULL(key_ptr[4]);
}