#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#include "env/sort_env.h"
#include <stdio.h>
#include <string.h>

CTEST_DATA(sort_environment)
{
    t_env *env;
    char *export_arguments[7];
    char *unset_arguments[3];
};

CTEST_SETUP(sort_environment)
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

    export(data->env, data->export_arguments);
};

CTEST_TEARDOWN(sort_environment)
{
    destroy_env(data->env, ENV_SIZE);
};

CTEST2(sort_environment, many_vars)
{
    (void)data;
    int sorted[ENV_SIZE] = {0, 1, 2, 3, 4}; //before: banana, cheese, apple, pear, a
    int expected[ENV_SIZE] = {4, 2, 0, 1, 3}; //expects: a, apple, banana, cheese, pear

    populate_env_index_buffer(sorted);
    sort_env(get_environment(), sorted);
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
    ASSERT_EQUAL(expected[2], sorted[2]);
    ASSERT_EQUAL(expected[3], sorted[3]);
    ASSERT_EQUAL(expected[4], sorted[4]);
}

CTEST2(sort_environment, populate_buffer)
{
    unset(get_environment(), data->unset_arguments); // now index 1 is empty
    
    int sorted[BUFFER_SIZE] = {0};
    int expected[BUFFER_SIZE] = {0, 2, 3, 4};

    ASSERT_EQUAL(4, populate_env_index_buffer(sorted)); // returns num of indexes inserted
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
    ASSERT_EQUAL(expected[2], sorted[2]);
    ASSERT_EQUAL(expected[3], sorted[3]);
}

CTEST2(sort_environment, sort_env)
{
    unset(get_environment(), data->unset_arguments); // now index 1 is empty
    
    int sorted[BUFFER_SIZE] = {0};
    int expected[BUFFER_SIZE] = {4, 2, 0, 3};

    sort_env(data->env, sorted);
    ASSERT_EQUAL(expected[0], sorted[0]);
    ASSERT_EQUAL(expected[1], sorted[1]);
    ASSERT_EQUAL(expected[2], sorted[2]);
    ASSERT_EQUAL(expected[3], sorted[3]);

    display_sorted_env();
}
