#include <errors/errors.h>
#include <stdio.h>

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

// t_bool	should_exit(t_exit_code code)
// {

// }

// int    handle_error(t_exit_code code)
// {
// 	set_return_code(code);
// 	if (should_exit(code))
// 		exit(code);
// }