#include "ctest.h"
#include <output/run_commands.h>
#include <output/executor_utils.h>
#include <parser/get_executable_path.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>

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
        while ((command_array[i][size]) != SPACE)
            size++;
        char *cmd = ft_substr(command_array[i], 0, size);
        create_table(&commands[i], command_array[i], get_executable_path(cmd));
        free(cmd);
    }
}

CTEST(pipe_test, basic_setup_test)
{
    create_command_array();
    ASSERT_STR(get_executable_path("cat") ,commands[0].exe_path);
    ASSERT_STR(command_array[0] ,commands[0].arg.start);
    ASSERT_STR(get_executable_path("grep") ,commands[1].exe_path);
    ASSERT_NULL(commands[3].exe_path);
}

// CTEST(pipe_test, one_pipe)
// {
//     create_command_array();
//     int res1 = open("res1.txt", O_RDWR | O_CREAT, 0777);
//     int res2 = open("res2.txt", O_RDWR | O_CREAT, 0777);
//     dup2(res1, 1);
// }