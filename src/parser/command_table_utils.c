#include <libft.h>
#include <parser/command_table.h>
#include <parser/get_executable_path.h>

/*
	get_executable_path only returns a string if passed command or path,
	is executable.
	Thus if command->exe_path exists it's a valid system command
*/
t_bool	is_system_command(const char *input, t_command *command)
{
	const int	len = get_set_index(input, " |");
	char		cmd_buffer[4098];

	if (!input || !command)
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
