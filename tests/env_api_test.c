#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#define ENV_TEST_SIZE 50

CTEST_DATA(environment)
{
    t_env env[ENV_TEST_SIZE];
};

CTEST_SETUP(environment)
{
    for (int i = 0; i < ENV_TEST_SIZE; ++i)
    {
        data->env[i].key = NULL;
        data->env[i].value = NULL;
    }
};

CTEST_TEARDOWN(environment)
{
    destroy_env(data->env, ENV_TEST_SIZE);
};

CTEST2(environment, export_set)
{
    char *key = "TEST";
    char *value = "ENV";
    
    ASSERT_TRUE(export_env("TEST=ENV", data->env));
    ASSERT_STR(data->env[0].key, key);
    ASSERT_STR(value, data->env[0].value);
}

CTEST2(environment, export_many_sets)
{
    char *pairs[8] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    int i = 0;
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
  
    ASSERT_STR(data->env[0].key, "TEST_1");
    ASSERT_STR(data->env[0].value, "ENV_1");
    ASSERT_STR(data->env[1].key, "TEST_2");
    ASSERT_STR(data->env[1].value, "ENV_2");
    ASSERT_STR(data->env[2].key, "TEST_3");
    ASSERT_STR(data->env[2].value, "ENV_3");
    ASSERT_STR(data->env[3].key, "TEST_4");
    ASSERT_STR(data->env[3].value, "ENV_4");
}

CTEST2(environment, unset_pair)
{
    char *pairs[8] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    int i = 0;
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));

    ASSERT_STR(data->env[0].key, "TEST_1");
    ASSERT_STR(data->env[0].value, "ENV_1");
    ASSERT_STR(data->env[1].key, "TEST_2");
    ASSERT_STR(data->env[1].value, "ENV_2");
    ASSERT_STR(data->env[2].key, "TEST_3");
    ASSERT_STR(data->env[2].value, "ENV_3");
    ASSERT_STR(data->env[3].key, "TEST_4");
    ASSERT_STR(data->env[3].value, "ENV_4");

    unset_env("TEST_2", data->env);
    ASSERT_NULL(data->env[1].key);
    ASSERT_NULL(data->env[1].value);
}


CTEST2(environment, unset_pair_does_not_exist)
{
    char *pairs[8] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    int i = 0;
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));
    ASSERT_TRUE(export_env(pairs[i++], data->env));

    ASSERT_STR(data->env[0].key, "TEST_1");
    ASSERT_STR(data->env[0].value, "ENV_1");
    ASSERT_STR(data->env[1].key, "TEST_2");
    ASSERT_STR(data->env[1].value, "ENV_2");
    ASSERT_STR(data->env[2].key, "TEST_3");
    ASSERT_STR(data->env[2].value, "ENV_3");
    ASSERT_STR(data->env[3].key, "TEST_4");
    ASSERT_STR(data->env[3].value, "ENV_4");

    unset_env("TEST_5", data->env);
}