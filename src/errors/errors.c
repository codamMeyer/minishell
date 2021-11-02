#include <errors/errors.h>
#include <stdio.h>
#include <defines.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <output/write_to_std.h>
#include <executor/run_commands.h>

t_exit_code	*get_return_code(void)
{
	static t_exit_code code = 0;

	return (&code);
}

t_exit_code    set_return_code(t_exit_code new_code)
{
	t_exit_code *code;

    code = get_return_code();
    *code = new_code;
	return (*code);
}

static t_bool	should_exit(t_exit_code code)
{
	if (code == MALLOC_ERROR || \
		code == DUP_ERROR || \
		code == FORK_ERROR || \
		code ==  PIPE_ERROR)
	{
		set_return_code(SYS_ERROR);
		return (TRUE);
	}
	return (FALSE);
}

static void	write_system_error(t_exit_code code, const char *location, const char *filename)
{
	if (code == FILE_ERROR || \
		code == SYS_ERROR || \
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
		set_return_code(SYS_ERROR);
	}
}

void    handle_error(t_exit_code code, const char *location, const char *filename)
{
	if (code == SUCCESS)
		return ;
	set_return_code(code);
	write_to_stderr("BestShellEver: ");
	if (code == HOME_NOT_SET_ERROR)
	{
		write_to_stderr(location);
		write_to_stderr("HOME not set\n");
	}
	else if (code == SYNTAX_ERROR)
	{
		write_to_stderr(location);
		write_to_stderr(filename);
	}
	else
		write_system_error(code, location, filename);
	if (should_exit(code))
		exit(*get_return_code());
}