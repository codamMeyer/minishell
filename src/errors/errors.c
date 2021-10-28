#include <errors/errors.h>
#include <stdio.h>
#include <defines.h>
#include <stdlib.h>
#include <output/write_to_std.h>

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
	return (code == MALLOC_ERROR);
}

void    handle_error(t_exit_code code)
{
	const static char *error_string[] = {
										"",
										"",
										"Malloc Error\n"
										};
	set_return_code(code);
	write_to_stderr("Minishell: ");
	write_to_stderr(error_string[code]);
	if (should_exit(code))
		exit(code);
}