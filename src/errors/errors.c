#include <errors/errors.h>
#include <stdio.h>

int	*get_return_code(void)
{
	static int code = 0;

	return (&code);
}

int    set_return_code(int new_code)
{
	int *code;
    
    code = get_return_code();
    *code = new_code;
	return (*code);
}