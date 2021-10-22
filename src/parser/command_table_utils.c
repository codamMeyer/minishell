#include <libft.h>
#include <stdlib.h>
#include <parser/command_table.h>
#include <parser/get_executable_path.h>

t_command	*expand_arg_content(t_command *command, t_buffer *buffer)
{
	while (command->arg.start < command->arg.end)
		append_expanded_input_to_buffer((t_arg *)&command->arg, buffer);
	command->arg.start = (char *)buffer->buf;
	command->code = get_command_code(&command->arg.start, command);
	command->arg.len = ft_strlen(command->arg.start);
	command->arg.end = command->arg.start + command->arg.len;
	if (command->code == SYSTEM && \
		!is_system_command(command->arg.start, command))
		command->code = INVALID;
	return (command);
}

/*
	get_executable_path only returns a string if passed command or path,
	is executable.
	Thus if command->exe_path exists it's a valid system command
*/
t_bool	is_system_command(const char *input, t_command *command)
{
	const int	len = get_set_index(input, " |");
	char		cmd_buffer[4098];

	if (!input || !command || *input == PIPE)
		return (FALSE);
	ft_strlcpy(&cmd_buffer[0], input, len + 1);
	command->exe_path = get_executable_path(&cmd_buffer[0]);
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
		++i;
	}
}
