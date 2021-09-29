#include "ctest.h"
#include <executor/run_commands.h>
#include <executor/executor_utils.h>
#include <parser/get_executable_path.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>

void	create_table(t_command commands[], char *arg, char *path)
{
	commands->arg.start = arg;
	commands->arg_len = strlen(arg);
	commands->exe_path = path;
}

t_command commands[50];
int array_size = sizeof(commands);
int number_of_commands = 3;
char *command_array[] = {"cat main.c", "grep int", "cat -e"}; 

void    create_command_array()
{
    bzero(&commands[0], sizeof(commands));
    for (int i = 0; i < number_of_commands; i++)
    {
        int size = 0;
        while ((command_array[i][size]) != SPACE_CHAR)
            size++;
        char *cmd = ft_substr(command_array[i], 0, size);
        char *path = get_executable_path(cmd);
        create_table(&commands[i], command_array[i], path);
        free(cmd);
    }
}

CTEST(pipe_test, basic_setup_test)
{
    char *path = NULL;
    create_command_array();
    path = get_executable_path("cat");
    ASSERT_STR(path ,commands[0].exe_path);
    free((char *)commands[0].exe_path);
    free(path);
    path = get_executable_path("grep");
    ASSERT_STR(command_array[0] ,commands[0].arg.start);
    ASSERT_STR(path, commands[1].exe_path);
    free((char *)commands[1].exe_path);
    free(path);
    path = NULL;
    ASSERT_NULL(commands[3].exe_path);
}

// CTEST(pipe_test, one_pipe)
// {
//     create_command_array();
//     int res1 = open("res1.txt", O_RDWR | O_CREAT, 0777);
//     int res2 = open("res2.txt", O_RDWR | O_CREAT, 0777);
//     dup2(res1, 1);
// }