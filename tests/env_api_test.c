#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"
#include <stdio.h>

CTEST_DATA(environment)
{
    t_env *env;
};

CTEST_SETUP(environment)
{
    data->env = get_environment();
};

CTEST_TEARDOWN(environment)
{
    destroy_env(data->env, ENV_SIZE);
};

CTEST2(environment, ensure_env_is_set_to_null)
{
    (void)data;
    for (int i = 0; i < ENV_SIZE; ++i)
    {
        ASSERT_NULL(get_environment()[i].key);
        ASSERT_NULL(get_environment()[i].value);
    }
}

CTEST2(environment, export_wrong_set)
{
    ASSERT_FALSE(export(data->env, "TEST ENV"));
}

CTEST2(environment, export_set)
{
    char *key = "TEST";
    char *value = "ENV";
    
    ASSERT_TRUE(export(data->env, "TEST=ENV"));
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
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));
  
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
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    ASSERT_STR(data->env[0].key, "TEST_1");
    ASSERT_STR(data->env[0].value, "ENV_1");
    ASSERT_STR(data->env[1].key, "TEST_2");
    ASSERT_STR(data->env[1].value, "ENV_2");
    ASSERT_STR(data->env[2].key, "TEST_3");
    ASSERT_STR(data->env[2].value, "ENV_3");
    ASSERT_STR(data->env[3].key, "TEST_4");
    ASSERT_STR(data->env[3].value, "ENV_4");

    unset(data->env, "TEST_2");
    ASSERT_NULL(data->env[1].key);
    ASSERT_NULL(data->env[1].value);
}

CTEST2(environment, unset_pair_does_not_exist)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    ASSERT_STR(data->env[0].key, "TEST_1");
    ASSERT_STR(data->env[0].value, "ENV_1");
    ASSERT_STR(data->env[1].key, "TEST_2");
    ASSERT_STR(data->env[1].value, "ENV_2");
    ASSERT_STR(data->env[2].key, "TEST_3");
    ASSERT_STR(data->env[2].value, "ENV_3");
    ASSERT_STR(data->env[3].key, "TEST_4");
    ASSERT_STR(data->env[3].value, "ENV_4");

    unset(data->env, "TEST_5");
}

void display_func(const char *str)
{
    printf("%s", str);
}

CTEST2(environment, display)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    unset(data->env, "TEST_2");
    printf("\n");
    display_env(data->env, display_func);
}

CTEST2(environment, find_non_existent_name)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    unset(data->env, "TEST_2");
    ASSERT_NULL(find_variable(data->env, "TEST_2"));
}

CTEST2(environment, find_value)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    unset(data->env, "TEST_2");
    ASSERT_STR(find_variable(data->env, "TEST_1")->value, "ENV_1");
}

CTEST2(environment, find_value_with_name_almost_equal)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));
    ASSERT_NULL(find_variable(data->env, "TEST"));
}

CTEST2(environment, export_new_value_for_existent_key)
{
    char *pairs[5] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
        "TEST_2=ENV_2_NEW_VALUE",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    ASSERT_TRUE(export(data->env, pairs[4]));
    ASSERT_STR(find_variable(data->env, "TEST_2")->value, "ENV_2_NEW_VALUE");
}

CTEST2(environment, export_two_variables_together)
{
    char *pairs[3] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2       TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 3; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));

    ASSERT_STR(find_variable(data->env, "TEST_3")->value, "ENV_3");
}

CTEST2(environment, export_with_double_quotes)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=\"ENV_2    TEST\"",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        export(data->env, pairs[i]);
    ASSERT_STR(find_variable(data->env, "TEST_2")->value, "ENV_2    TEST");
}

CTEST2(environment, export_with_double_quotes_and_var)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2=\"ENV_2    $TEST_1\"",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        export(data->env, pairs[i]);
    ASSERT_STR(find_variable(data->env, "TEST_2")->value, "ENV_2    ENV_1");
}

CTEST2(environment, export_with_var_in_the_key)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2$TEST_1=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        export(data->env, pairs[i]);
    ASSERT_STR(find_variable(data->env, "TEST_2ENV_1")->key, "TEST_2ENV_1");
}

CTEST2(environment, export_with_single_quotes)
{
    char *pairs[4] = {
        "TEST_1=ENV_1",
        "TEST_2='ENV_2    $TEST_1'",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    for (int i = 0; i < 4; ++i)
        ASSERT_TRUE(export(data->env, pairs[i]));
    ASSERT_STR(find_variable(data->env, "TEST_2")->value, "ENV_2    $TEST_1");
}

CTEST2(environment, empty_value)
{
    char *pair = "key=";
    
    ASSERT_TRUE(export(data->env, pair));
    ASSERT_STR(find_variable(data->env, "key")->value, "");
}

CTEST2(environment, string_with_single_quote_as_value)
{
    char *pair = "key='test with single quotes'";
    
    ASSERT_TRUE(export(data->env, pair));
    ASSERT_STR(find_variable(data->env, "key")->value, "test with single quotes");
}