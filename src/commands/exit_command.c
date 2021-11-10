#include <libft.h>
#include <commands/commands.h>

static	t_bool	has_only_nums(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	is_invalid_exit_code(int exit_code,
						const char *str, int arg_len)
{
	return (!has_only_nums(str) || (exit_code == -1 && arg_len >= 19));
}

static t_exit_code	get_exit_value(char *exit_string)
{
	const int	exit_str_len = ft_strlen(exit_string);
	t_exit_code	exit_code;

	exit_code = ft_atoi(exit_string);
	if (is_invalid_exit_code(exit_code, exit_string, exit_str_len))
	{
		handle_error(EXIT_ARGS_ERROR, "exit: ", exit_string);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (255);
	}
	else if (exit_code == -1 && exit_str_len > 2)
		exit_code = 255;
	else if (exit_code == -2 && exit_str_len > 2)
		exit_code = 0;
	return (exit_code);
}

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout)
{
	t_exit_code	exit_code;

	(void)write_to_stdout;
	if (!command.arguments[1])
		exit(SUCCESS);
	exit_code = get_exit_value(command.arguments[1]);
	if (command.arguments[2] && has_only_nums(command.arguments[1]))
	{
		handle_error(EXIT_ARGS_ERROR, "exit:", " too many arguments\n");
		return (ERROR);
	}
	exit(exit_code);
	return (exit_code);
}
