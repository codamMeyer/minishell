#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <executor/executor_utils.h>
#include <parser/parse_redirection.h>
#include <readline/readline.h>
#include <readline/history.h>

void	open_infile(const char *file, int *in_file)
{
	if (*in_file != INVALID_FD)
		close(*in_file);
	*in_file = open(file, O_RDONLY, 0644);
	if (*in_file == INVALID_FD)
	{
		printf("Couldn't open in file: %s\n", file);
		exit(1);
	}
}

void	open_outfile(const char *file, int *out_file, int out_mode)
{
	if (*out_file != INVALID_FD)
		close(*out_file);
	*out_file = open(file, O_RDWR | O_CREAT | out_mode, FILE_RIGHTS);
	if (*out_file == INVALID_FD)
	{
		printf("Couldn't open in file: %s\n", file);
		exit(1);
	}
}
