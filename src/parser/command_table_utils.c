#include <libft.h>
#include <stdlib.h>
#include <parser/command_table.h>
#include <parser/get_executable_path.h>
#include <parser/arguments.h>

/* If command->exe_path exists it's a valid system command */
t_bool	is_system_command(const char *input, t_command *command)
{
	if (!input || !command || *input == PIPE)
		return (FALSE);
	command->exe_path = get_executable_path(input);
	if (command->exe_path)
		return (TRUE);
	return (FALSE);
}

char	*get_set_position(const char *set, char *str_to_check)
{
	int	i;

	i = 0;
	while (str_to_check && str_to_check[i])
	{
		if (ft_strchr(set, str_to_check[i]))
			return (&str_to_check[i]);
		++i;
	}
	return (NULL);
}

void	cleanup_command_table(t_command *command_table, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		if (command_table[i].code == SYSTEM)
			free((char *)command_table[i].exe_path);
		if (command_table->files.in > 0)
			close(command_table->files.in);
		if (command_table->files.out > 0)
			close(command_table->files.out);
		destroy_split_arg(command_table[i].arguments);
		++i;
	}
}
