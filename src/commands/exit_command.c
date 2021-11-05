#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <commands/commands.h>
#include <parser/parser.h>

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
	return (!has_only_nums(str)
		|| (exit_code == -1 && arg_len >= 19));
}

static t_exit_code	get_exit_value(t_buffer *exit, int arg_len)
{
	t_exit_code	exit_code;

	exit_code = ft_atoi(exit->buf);
	if (is_invalid_exit_code(exit_code, exit->buf, arg_len))
	{
		handle_error(EXIT_ARGS_ERROR, "exit: ", exit->buf);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (exit_code == -1)
		exit_code = 255;
	else if (exit_code == -2 && arg_len > 2)
		exit_code = 0;
	return (exit_code);
}

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout)
{
	t_exit_code	exit_code;
	t_buffer	buffer;

	(void)write_to_stdout;
	init_buffer(&buffer);
	while (command.arg.start < command.arg.end
		&& *command.arg.start != SPACE_CHAR)
		append_expanded_input_to_buffer(&command.arg, &buffer);
	skip_spaces(&command.arg.start);
	if (ft_isalnum(*command.arg.start))
	{
		handle_error(EXIT_ARGS_ERROR, "exit:", " too many arguments\n");
		return (1);
	}
	exit_code = get_exit_value(&buffer, command.arg.len);
	exit(exit_code);
	return (exit_code);
}
