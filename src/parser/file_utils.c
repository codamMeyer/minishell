#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <ctype.h>
#include <executor/executor_utils.h>
#include <parser/parse_redirection.h>
#include <readline/readline.h>
#include <readline/history.h>

t_bool	is_valid_filename_char(char c, int redirect_id)
{
	if (redirect_id == HERE_DOC)
		return (FALSE);
	return (c && !isspace(c)
		&& !ft_strchr(ALL_TERMINATORS, c));
}

void	open_infile(const char *file, int *in_file)
{
	if (*in_file != INVALID_FD)
		close(*in_file);
	*in_file = open(file, O_RDONLY, 0644);
	if (*in_file == SYS_ERROR)
	{
		*in_file = FILE_ERROR;
		printf("minishell: %s: No such file or directory\n", file);
	}
}

void	open_outfile(const char *file, int *out_file, int out_mode)
{
	if (*out_file != INVALID_FD)
		close(*out_file);
	*out_file = open(file, O_RDWR | O_CREAT | out_mode, FILE_RIGHTS);
	if (*out_file == INVALID_FD)
	{
		printf("Couldn't open in outfile: %s\n", file);
		exit(1);
	}
}
