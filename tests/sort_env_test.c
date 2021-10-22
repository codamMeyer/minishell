#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#include "env/sort_env.h"
#include <stdio.h>
#include <string.h>

CTEST_DATA(sort_environment)
{
    t_env *env;
};

CTEST_SETUP(sort_environment)
{
    data->env = get_environment();
};

CTEST_TEARDOWN(sort_environment)
{
    destroy_env(data->env, ENV_SIZE);
};

CTEST2(sort_environment, two_vars)
{
    export(data->env, "banana=1");
    export(data->env, "apple=2");
    
    int sorted[ENV_SIZE] = {0, 1}; //original banana, apple
    int expected[ENV_SIZE] = {1, 0}; //expects apple, banana

    int i = 0;
    int j = 1;
    int tmp;

    if (strcmp(data->env[sorted[i]].key, data->env[sorted[j]].key) > 0)
    {
        tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
    }
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
}

CTEST2(sort_environment, populate_buffer)
{
    export(data->env, "banana=0");
    export(data->env, "cheese=1");
    export(data->env, "apple=2");
    export(data->env, "pear=3");
    unset(get_environment(), "cheese"); // now index 1 is empty
    
    int sorted[BUFFER_SIZE] = {0};
    int expected[BUFFER_SIZE] = {0, 2, 3};

    ASSERT_EQUAL(3, populate_env_index_buffer(sorted)); // returns num of indexes inserted
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
    ASSERT_EQUAL(expected[2], sorted[2]);
}

CTEST2(sort_environment, sort_env)
{
    export(data->env, "banana=0");
    export(data->env, "cheese=1");
    export(data->env, "apple=2");
    export(data->env, "pear=3");
    export(data->env, "a=4");
    unset(get_environment(), "cheese"); // now index 1 is empty
    
    int sorted[BUFFER_SIZE] = {0};
    int expected[BUFFER_SIZE] = {4, 2, 0, 3};

    sort_env(sorted);
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
    ASSERT_EQUAL(expected[2], sorted[2]);
    ASSERT_EQUAL(expected[3], sorted[3]);

    display_sorted_env();
}
