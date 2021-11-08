#include "ctest.h"
#include <string.h>
#include "env/environment.h"
#include "arguments.h"

CTEST_DATA(split_command_arg)
{
    t_env   *env;
    char    **args;
};

CTEST_SETUP(split_command_arg)
{
    data->env = get_environment();
    export(data->env, "TEST1=hello TEST2=\"this     is     a       string\" TEST3=\"=\"");
};

CTEST_TEARDOWN(split_command_arg)
{
    destroy_env(data->env, ENV_SIZE);
    destroy_splited_arg(data->args);
};

CTEST2(split_command_arg, empty_arg)
{
    t_arg command_arg;
    const char *inp = "";
    command_arg.start = inp;
    command_arg.end = inp;
    command_arg.len = 0;

    data->args = split_command_args(command_arg);
    ASSERT_NULL(data->args[0]);
}

CTEST2(split_command_arg, only_spaces)
{
    t_arg command_arg;
    const char *inp = "\t     \t   \v";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_NULL(data->args[0]);
}

CTEST2(split_command_arg, one_word_arg)
{
    t_arg command_arg;
    const char *inp = "\tword\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("word", data->args[0]);
    ASSERT_NULL(data->args[1]);
}


CTEST2(split_command_arg, one_word_arg_between_quotes)
{
    t_arg command_arg;
    const char *inp = "\t\"word\"\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("word", data->args[0]);
    ASSERT_NULL(data->args[1]);
}

CTEST2(split_command_arg, with_env_variables)
{
    t_arg command_arg;
    const char *inp = "\t\"  $TEST2  \" \t $TEST2\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("  this     is     a       string  ", data->args[0]);
    ASSERT_STR("this", data->args[1]);
    ASSERT_STR("is", data->args[2]);
    ASSERT_STR("a", data->args[3]);
    ASSERT_STR("string", data->args[4]);
    ASSERT_NULL(data->args[5]);
}

CTEST2(split_command_arg, string_variable_inside_quotes)
{
    t_arg command_arg;
    const char *inp = "\t\"$TEST2\" \t $TEST1\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("this     is     a       string", data->args[0]);
    ASSERT_STR("hello", data->args[1]);
    ASSERT_NULL(data->args[2]);
}

CTEST2(split_command_arg, export_example)
{
    t_arg command_arg;
    const char *inp = "test\"=\"hello  \"test1=hey\"   test2=\"this is a string\"  test3\"$TEST3\"hehe";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("test=hello", data->args[0]);
    ASSERT_STR("test1=hey", data->args[1]);
    ASSERT_STR("test2=this is a string", data->args[2]);
    ASSERT_STR("test3=hehe", data->args[3]);
    ASSERT_NULL(data->args[4]);
}


CTEST2(split_command_arg, one_word_arg_between_single_quotes)
{
    t_arg command_arg;
    const char *inp = "\t\'word\'\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("word", data->args[0]);
    ASSERT_NULL(data->args[1]);
}

CTEST2(split_command_arg, with_env_variables_inside_single_quotes)
{
    t_arg command_arg;
    const char *inp = "\t\'  $TEST2  \' \t $TEST2\t";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("  $TEST2  ", data->args[0]);
    ASSERT_STR("this", data->args[1]);
    ASSERT_STR("is", data->args[2]);
    ASSERT_STR("a", data->args[3]);
    ASSERT_STR("string", data->args[4]);
    ASSERT_NULL(data->args[5]);
}


CTEST2(split_command_arg, export_example_with_single_quotes)
{
    t_arg command_arg;
    const char *inp = "test\"=\"hello  \"test1=hey\"   test2=\"this is a string\"  test3\'$TEST3\'hehe";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("test=hello", data->args[0]);
    ASSERT_STR("test1=hey", data->args[1]);
    ASSERT_STR("test2=this is a string", data->args[2]);
    ASSERT_STR("test3$TEST3hehe", data->args[3]);
    ASSERT_NULL(data->args[4]);
}


CTEST2(split_command_arg, empty_quotes)
{
    t_arg command_arg;
    const char *inp = "\"\"";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("", data->args[0]);
    ASSERT_NULL(data->args[1]);
}

CTEST2(split_command_arg, single_quotes_inside_double_quotes)
{
    t_arg command_arg;
    const char *inp = "\"'$TEST2'\"";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("'this     is     a       string'", data->args[0]);
    ASSERT_NULL(data->args[1]);
}

CTEST2(split_command_arg, double_quotes_inside_single_quotes)
{
    t_arg command_arg;
    const char *inp = "'\"$TEST2\"'";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("\"$TEST2\"", data->args[0]);
    ASSERT_NULL(data->args[1]);
}


CTEST2(split_command_arg, double_quotes_inside_single_quotes_inside_str)
{
    t_arg command_arg;
    const char *inp = "helloThisIsATest'\"$TEST2\"'";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR("helloThisIsATest\"$TEST2\"", data->args[0]);
    ASSERT_NULL(data->args[1]);
}


CTEST2(split_command_arg, export_blah)
{
    t_arg command_arg;
    const char *inp = "\" $TEST1 \"=\"$TEST2\"";
    const int   inp_len = strlen(inp);
    command_arg.start = inp;
    command_arg.end = inp + inp_len;
    command_arg.len = inp_len;

    data->args = split_command_args(command_arg);
    ASSERT_STR(" hello =this     is     a       string", data->args[0]);
    ASSERT_NULL(data->args[1]);
}