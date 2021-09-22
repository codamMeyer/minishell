#include <commands/commands.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <parser/here_doc.h>
#include <stdio.h>
#include <fcntl.h>

/*
	Assumes that string has been checked for quotes
*/
int	get_file_name_and_length(char *buffer, char *input)
{
	const int	file_name_len = get_arg_len(input, SPECIALS);
	int			len_to_cpy;
	char		*cursor;

	ft_bzero(&buffer[0], BUFFER_SIZE);
	cursor = input;
	if (*cursor == DOUBLE_QUOTES)
	{
		++(cursor);
		len_to_cpy = file_name_len - 2;
	}
	else
		len_to_cpy = file_name_len;
	ft_strlcpy(&buffer[0], cursor, len_to_cpy + 1);
	return (file_name_len);
}

int	get_redirect_id(const char *cursor)
{
	if (*cursor == LEFT_ANGLE && *(cursor + 1) != LEFT_ANGLE)
		return (LEFT_ANGLE);
	else if (*cursor == RIGHT_ANGLE && *(cursor + 1) != RIGHT_ANGLE)
		return (RIGHT_ANGLE);
	else if (ft_strncmp(cursor, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(cursor, ">>", 2) == 0)
		return (APPEND);
	return (-1);
}

/*
	Might still split this into diff functions
*/
void	open_in_mode(const char *file, t_files *files, int mode_id)
{
	if (mode_id == LEFT_ANGLE)
		open_infile(file, &files->in);
	else if (mode_id == RIGHT_ANGLE || mode_id == APPEND)
		open_outfile(file, &files->out, mode_id);
	else if (mode_id == HERE_DOC)
		handle_here_doc(file, &files->in);
}

/*
	i keeps trtack of how many chars need to be
	replaced by spaces
*/
int	open_file(char *file_name_ptr, t_files *files, int redirection_id)
{
	char	buffer[BUFFER_SIZE];
	int		i;

	i = count_consecutive_spaces(file_name_ptr);
	i += get_file_name_and_length(&buffer[0], &file_name_ptr[i]);
	open_in_mode((const char *)buffer, files, redirection_id);
	return (i);
}

/*
	return t_files which have an int for the in and out fd's respectively
*/
t_files	get_redirection(char **input, const int string_to_parse_len)
{
	int		index;
	int		length;
	int		redirect_id;
	t_files	fd;
	char	*cursor;

	fd.in = INVALID_FD;
	fd.out = INVALID_FD;
	cursor = *input;
	index = get_arg_len(&cursor[0], "><") + 1;
	while (index < string_to_parse_len)
	{
		redirect_id = get_redirect_id(&cursor[index - 1]);
		if (redirect_id == APPEND || redirect_id == HERE_DOC)
			index += 1;
		length = open_file(&cursor[index], &fd, redirect_id);
		if (redirect_id == APPEND || redirect_id == HERE_DOC)
			index -= 1;
		replace_redirection_w_space(input, length + 2, index - 1);
		index += get_arg_len(&cursor[index], "><") + 1;
	}
	return (fd);
}
