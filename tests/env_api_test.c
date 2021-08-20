#include "ctest.h"
#include <stdlib.h>
#include "env/environment.h"

CTEST(export_env, export_set)
{
    char *key = "TEST";
    char *value = "ENV";
    t_env env[5];
    for (int i = 0; i < 4; ++i)
    {
        env[i].key = NULL;
        env[i].value = NULL;
    }
    
    ASSERT_TRUE(export_env_set("TEST=ENV", env));
    ASSERT_STR(env[0].key, key);
    ASSERT_STR(value, env[0].value);
    destro_env_set(&env[0]);
}

CTEST(export_env, export_many_sets)
{
    char *pairs[8] = {
        "TEST_1=ENV_1",
        "TEST_2=ENV_2",
        "TEST_3=ENV_3",
        "TEST_4=ENV_4",
    };
    
    t_env env[5];
    int i = 0;
    for (; i < 4; ++i)
    {
        env[i].key = NULL;
        env[i].value = NULL;
    }

    i = 0;
    ASSERT_TRUE(export_env_set(pairs[i++], env));
    ASSERT_TRUE(export_env_set(pairs[i++], env));
    ASSERT_TRUE(export_env_set(pairs[i++], env));
    ASSERT_TRUE(export_env_set(pairs[i++], env));
  
    ASSERT_STR(env[0].key, "TEST_1");
    ASSERT_STR(env[0].value, "ENV_1");
    ASSERT_STR(env[1].key, "TEST_2");
    ASSERT_STR(env[1].value, "ENV_2");
    ASSERT_STR(env[2].key, "TEST_3");
    ASSERT_STR(env[2].value, "ENV_3");
    ASSERT_STR(env[3].key, "TEST_4");
    ASSERT_STR(env[3].value, "ENV_4");
    
    for (int j = 0; j < 4; ++j)
        destro_env_set(&env[j]);
}