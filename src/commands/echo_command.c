#include <ctype.h>
#include <commands/buffer.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/env_utils.h>
#include <parser/parser.h>

static void	handle_spaces(t_arg *arg, t_buffer *buffer)
{
	if (isspace(*arg->start) && buffer->index)
	{
		skip_spaces(&arg->start);
		if (arg->start != arg->end)
		{	
			buffer->buf[buffer->index] = SPACE_CHAR;
			++(buffer->index);
		}
	}
}

static int	handle_empty_str(t_bool has_n_flag, t_output_stdout output)
{
	if (has_n_flag)
		output("");
	else
		output("\n");
	return (SUCCESS);
}

t_bool	is_empty_buffer(t_buffer *buffer)
{
	int	i;

	i = 0;
	while (i < buffer->index)
	{
		if (!isspace(buffer->buf[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_exit_code	echo_command(t_command command, t_output_stdout output)
{
	const t_bool	has_n_flag = parse_n_flag((t_arg *)&command.arg);
	t_buffer		buffer;

	init_buffer(&buffer);
	if (command.arg.len == 0)
		return (handle_empty_str(has_n_flag, output));
	while (command.arg.start < command.arg.end)
	{
		append_expanded_input_to_buffer(&command.arg, &buffer);
		handle_spaces(&command.arg, &buffer);
	}
	if (!has_n_flag)
		buffer.buf[buffer.index] = '\n';
	output(&buffer.buf[0]);
	return (SUCCESS); 
}
