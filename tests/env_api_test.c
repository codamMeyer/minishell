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
        ASSERT_NULL(get_environment()[i].set);
    }
}