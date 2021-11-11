#include <ctype.h>
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <commands/quotes.h>
#include <env/env_utils.h>
#include <executor/executor_utils.h>
#include <parser/command_table.h>
#include <parser/here_doc.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <parser/arguments.h>

/*
	Assumes that string has been checked for quotes
*/
int	get_file_name_and_length(t_buffer *buffer, char *input, int redirect_id)
{
	const int	len_to_replace = get_set_index(input, ALL_TERMINATORS) + 1;
	char		**split;
	t_arg		arg;

	arg.start = input;
	arg.end = input + (len_to_replace - 1);
	skip_spaces(&arg.start);
	if (redirect_id == HERE_DOC)
	{
		ft_strlcpy(&buffer->buf[0], input, len_to_replace);
		return (len_to_replace);
	}
	split = split_command_args(arg);
	if (!split)
	{
		handle_error(MALLOC_ERROR, MALLOC_STR, NULL);
		return (len_to_replace);
	}
	ft_strlcpy(&buffer->buf[0], split[0], ft_strlen(split[0]) + 1);
	destroy_split_arg(split);
	return (len_to_replace);
}

int	get_redirect_id(const char *cursor)
{
	if (ft_strncmp(cursor, "<<", 2) == SUCCESS)
		return (HERE_DOC);
	else if (ft_strncmp(cursor, ">>", 2) == SUCCESS)
		return (FT_APPEND);
	else if (ft_strncmp(cursor, "<>", 2) == SUCCESS)
		return (DIAMOND_BRACKETS);
	else if (*cursor == LEFT_ANGLE)
		return (LEFT_ANGLE);
	else if (*cursor == RIGHT_ANGLE)
		return (FT_TRUNCATE);
	return (INVALID);
}

t_exit_code	open_in_mode(const char *file, t_files *files, int mode_id)
{
	if (mode_id == LEFT_ANGLE || mode_id == DIAMOND_BRACKETS)
		return (open_infile(file, &files->in));
	else if (mode_id == FT_TRUNCATE || mode_id == FT_APPEND)
		return (open_outfile(file, &files->out, mode_id));
	else if (mode_id == HERE_DOC)
		files->in = handle_here_doc(file);
	return (SUCCESS);
}

/*
	i keeps trtack of how many chars need to be
	replaced by spaces
*/
int	open_file(char *file_name_ptr, t_files *files, int redirection_id)
{
	t_buffer	buffer;
	int			i;

	init_buffer(&buffer);
	if (is_multi_angled_bracket(redirection_id))
		file_name_ptr += 1;
	file_name_ptr += 1;
	i = count_consecutive_spaces(file_name_ptr);
	i += get_file_name_and_length(&buffer, &file_name_ptr[i], redirection_id);
	if (open_in_mode(&buffer.buf[0], files, redirection_id) < SUCCESS)
		return (INVALID_FD);
	return (i);
}

/*
	return t_files which have an int for the in and out fd's respectively
	SAFTEYCHECK for redirect ID?
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
	index = get_set_index(&cursor[0], "><");
	while (index < string_to_parse_len)
	{
		redirect_id = get_redirect_id(&cursor[index]);
		length = open_file(&cursor[index], &fd, redirect_id);
		if (length < 0)
			break ;
		if (is_multi_angled_bracket(redirect_id))
			++length;
		replace_redirection_w_space(input, length, index);
		index += get_set_index(&cursor[index], "><");
	}
	return (fd);
}
