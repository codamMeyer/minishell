#include <env/sort_env.h>
#include <env/environment.h>
#include <string.h>
#include <stdio.h>

int    populate_env_index_buffer(int buffer[])
{
    t_env *env = get_environment();
    int i = 0;
    int j = 0;
    while (i < BUFFER_SIZE)
    {
        if (env[i].key)
        {
            buffer[j] = i;
            ++j;
        }
        ++i;
    }
    return (j);
}

int    sort_env(int buffer[])
{
    t_env *env;
    int j;
    int i = 0;
    int tmp;

    env = get_environment();
    int max = populate_env_index_buffer(buffer);
    while (i < max)
    {
        j = 0;
        while (j < max - i - 1)
        {
            if (strcmp(env[buffer[j]].key, env[buffer[j + 1]].key) > 0)
            {
                tmp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = tmp;
            }
            ++j;
        }
        ++i;
    }
    return (max);
}

void display_sorted_env()
{
    int buffer[ENV_SIZE] = {};
    int num_elements = sort_env(buffer);
    int i = 0;
    t_env *env = get_environment();

    printf("\n");
    while (i < num_elements)
    {
        printf("--> %s=%s\n", env[buffer[i]].key, env[buffer[i]].value);
        ++i;
    }
}