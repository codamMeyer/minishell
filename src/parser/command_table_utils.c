#include "command_table.h"
#include "get_executable_path.h"
#include <../libft/libft.h>
#include <stdio.h>

int	get_cmd_len(const char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != SPACE)
		i++;
	return (i);
}

t_bool	is_system_command(const char *input, t_command *command)
{
	const int	arg_len = get_cmd_len(input);
	char		cmd_buffer[4098];

	if (!input || ! command)
		return (FALSE);
	ft_strlcpy(&cmd_buffer[0], input, arg_len + 1);
	command->exe_path = get_executable_path(&cmd_buffer[0]);
	if (command->exe_path)
		return (TRUE);
	return (FALSE);
}

char	*get_redirection_position(const char *set, char *str_to_check)
{
	int	i;

	i = 0;
	while (str_to_check[i])
	{
		if (ft_strchr(set, str_to_check[i]))
			return (&str_to_check[i]);
		++i;
	}
	return (NULL);
}
