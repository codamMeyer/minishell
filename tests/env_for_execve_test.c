#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#include "env/env_for_exec.h"
#include <stdio.h>
#include <string.h>

// CTEST_DATA(env_to_execve)
// {
//     t_env *env;
// };

// CTEST_SETUP(env_to_execve)
// {
//     data->env = get_environment();
// };

// CTEST_TEARDOWN(env_to_execve)
// {
//     destroy_env(data->env, ENV_SIZE);
// };

// CTEST2(env_to_execve, env_to_execve)
// {
//     export(data->env, "banana=0");
//     export(data->env, "cheese=1");
//     export(data->env, "apple=2");
//     export(data->env, "pear=3");
//     export(data->env, "a=4");
//     unset(get_environment(), "cheese");
    
//     char *key_ptr[BUFFER_SIZE] = {};
//     char *expected[BUFFER_SIZE] = {"banana=0", "apple=2", "pear=3", "a=4"};

//     env_to_char_pointer_array(key_ptr);

//     ASSERT_STR(expected[0], key_ptr[0]);
//     ASSERT_STR(expected[1], key_ptr[1]);
//     ASSERT_STR(expected[2], key_ptr[2]);
//     ASSERT_STR(expected[3], key_ptr[3]);
//     ASSERT_NULL(key_ptr[4]);
// }