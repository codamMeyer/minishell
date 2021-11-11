#include <libft.h>
#include <parser/parse_redirection.h>

t_exit_code	open_infile(const char *file, int *in_file)
{
	if (*in_file != INVALID_FD)
		handle_error(close(*in_file), CLOSE_STR, NULL);
	*in_file = open(file, O_RDONLY, 0644);
	if (*in_file == INVALID_FD)
	{
		*in_file = FILE_ERROR;
		handle_error(FILE_ERROR, NULL, file);
		return (FILE_ERROR);
	}
	return (SUCCESS);
}

t_exit_code	open_outfile(const char *file, int *out_file, int out_mode)
{
	if (*out_file != INVALID_FD)
		handle_error(close(*out_file), CLOSE_STR, NULL);
	*out_file = open(file, O_RDWR | O_CREAT | out_mode, FILE_RIGHTS);
	if (*out_file == INVALID_FD)
	{	
		*out_file = FILE_ERROR;
		handle_error(SYS_ERROR, NULL, file);
		return (FILE_ERROR);
	}
	return (SUCCESS);
}
