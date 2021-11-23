#include <errors/errors.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <output/write_to_std.h>

static t_bool	should_exit(t_exit_code code)
{
	if (code == MALLOC_ERROR || \
		code == DUP_ERROR || \
		code == FORK_ERROR || \
		code == PIPE_ERROR)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	write_execve_error(t_exit_code code, \
								const char *cmd, \
								const char *error_msg)
{
	write_to_stderr(SHELL_NAME);
	if (cmd)
		write_to_stderr(cmd);
	write_to_stderr(": ");
	if (error_msg)
		write_to_stderr(error_msg);
	write_to_stderr(NEW_LINE);
	set_exit_code(code);
}

static void	write_system_error(t_exit_code code, \
								const char *location, \
								const char *filename)
{
	if (code == FILE_ERROR || code == SYS_ERROR || \
		(code >= MALLOC_ERROR && code <= PIPE_ERROR))
	{
		if (location)
		{
			write_to_stderr(location);
			write_to_stderr(": ");
		}
		if (filename)
		{
			write_to_stderr(filename);
			write_to_stderr(": ");
		}
		write_to_stderr(strerror(errno));
		write_to_stderr("\n");
		set_exit_code(1);
	}
}

void	handle_error(t_exit_code code, \
					const char *location, \
					const char *filename)
{
	if (code == SUCCESS)
		return ;
	write_to_stderr(SHELL_NAME);
	if (code == HOME_NOT_SET_ERROR)
	{
		write_to_stderr(location);
		write_to_stderr("HOME not set\n");
	}
	else if (code == SYNTAX_ERROR || code == EXIT_ARGS_ERROR)
	{
		write_to_stderr(location);
		write_to_stderr(filename);
		set_exit_code(code);
	}
	else
		write_system_error(code, location, filename);
	if (should_exit(code))
		exit(*get_exit_code());
}
