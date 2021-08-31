#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "ctest.h"

t_files files;

CTEST(redirection_tests, basic_infile)
{
	const char	*str = "   < infile cat -e";
	char		buffer[4096];

	init_files(&files);
	files = get_redirection(&str, 1);
	ft_strlcpy(buffer, files.in, get_cmd_len(files.in) + 1);
	ASSERT_STR("infile", buffer);
	ASSERT_STR(" cat -e", str);
}

CTEST(redirection_tests, basic_outfile)
{
	const char	*str = " > outfile | next cmd";
	char		buffer[4096];
	
	init_files(&files);
	files = get_redirection(&str, 1);
	ft_strlcpy(buffer, files.out, get_cmd_len(files.out) + 1);
	ASSERT_STR("outfile", buffer);
	ASSERT_STR(" | next cmd", str);
}

CTEST_DATA(command_table_redirection_tests)
{
    t_command command_table[100];
};

CTEST_SETUP(command_table_redirection_tests)
{
    (void)data;
};

CTEST_TEARDOWN(command_table_redirection_tests)
{
    (void)data;
};

CTEST2(command_table_redirection_tests, one_command_echo)
{
    const char *input = "echo Hello you this is a test";
    ASSERT_EQUAL(1, populate_commands_table(input, data->command_table));
    ASSERT_EQUAL(ECHO, data->command_table[0].code);
    ASSERT_STR(" Hello you this is a test", data->command_table[0].arg.start);
}


CTEST2(command_table_redirection_tests, basic_in_and_outfile_one_command)
{
	const char	*input = "< infile pwd > outfile";
	char		in_buffer[400];
	char		out_buffer[400];
	
	ASSERT_EQUAL(1, populate_commands_table(input, data->command_table));
	ASSERT_EQUAL(PWD, data->command_table[0].code);
	ft_strlcpy(in_buffer, data->command_table[0].files.in, get_cmd_len(data->command_table[0].files.in) + 1);
	ft_strlcpy(out_buffer, data->command_table[0].files.out, get_cmd_len(data->command_table[0].files.out) + 1);
	ASSERT_STR("infile", in_buffer);
	ASSERT_STR("outfile", out_buffer);
}

