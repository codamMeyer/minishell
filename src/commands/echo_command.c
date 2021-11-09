#include <libft.h>
#include <commands/buffer.h>
#include <commands/commands.h>
#include <commands/quotes.h>
#include <env/env_utils.h>
#include <parser/parser.h>
#include <errors/errors.h>
#include <arguments.h>

static t_bool	is_valid_n_flag_extras(const char **input)
{
	char	cursor;
	int		counter;

	counter = 2;
	cursor = (*(*input + counter));
	while (cursor == 'n')
	{
		counter++;
		cursor = (*(*input + counter));
	}
	if (cursor != NULL_TERMINATOR)
		return (FALSE);
	*input += counter;
	return (TRUE);
}

static t_bool	parse_n_flag(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_strncmp(str, N_FLAG, ft_strlen(N_FLAG)) == 0)
	{
		if (!is_valid_n_flag_extras((const char **)&str))
			return (FALSE);
		parse_n_flag(str);
		return (TRUE);
	}
	return (FALSE);
}

t_exit_code	echo_command(t_command command, t_output_stdout output)
{
	t_bool	has_n_flag;
	int		i;

	i = 0;
	if (!command.arguments)
	{
		handle_error(MALLOC_ERROR, NULL, "malloc()");
		return (MALLOC_ERROR);
	}
	has_n_flag = parse_n_flag(command.arguments[i]);
	while (has_n_flag && parse_n_flag(command.arguments[i]))
		++i;
	while (command.arguments[i])
	{
		output(command.arguments[i]);
		if (command.arguments[i + 1])
			output(" ");
		++i;
	}
	if (!has_n_flag)
		output("\n");
	return (SUCCESS);
}
