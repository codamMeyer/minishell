#include <fcntl.h>
#include <parser/parse_redirection.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <executor/executor_utils.h>

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
	*out_file = open(file, O_RDWR | O_CREAT | out_mode, 0664);
	if (*out_file == INVALID_FD)
	{
		printf("Couldn't open in file: %s\n", file);
		exit(1);
	}
}

// t_files	get_redirection(char **input, const int string_to_parse_len)
// {
// 	int		index;
// 	int		length;
// 	int		redirect_id;
// 	t_files	fd;
// 	char	*cursor;

// 	fd.in = INVALID_FD;
// 	fd.out = INVALID_FD;
// 	cursor = *input;
// 	index = get_arg_len(&cursor[0], "><") + 1;
// 	while (index < string_to_parse_len)
// 	{
// 		redirect_id = get_redirect_id(&cursor[index - 1]);
// 		if (redirect_id == FT_APPEND || redirect_id == HERE_DOC)
// 			index += 1;
// 		length = open_file(&cursor[index], &fd, redirect_id);
// 		if (redirect_id == FT_APPEND || redirect_id == HERE_DOC)
// 			index -= 1;
// 		replace_redirection_w_space(input, length + 2, index - 1);
// 		index += get_arg_len(&cursor[index], "><") + 1;
// 	}
// 	return (fd);
// }