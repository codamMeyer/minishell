#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <executor/executor_utils.h>
#include <parser/command_table.h>
#include <parser/here_doc.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>

/*
	Assumes that string has been checked for quotes
*/
int	get_file_name_and_length(char *buffer, char *input)
{
	const int	file_name_len = get_set_index(input, ALL_TERMINATORS) + 1;
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
	ft_strlcpy(&buffer[0], cursor, len_to_cpy);
	return (file_name_len);
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

void	open_in_mode(const char *file, t_files *files, int mode_id)
{
	if (mode_id == LEFT_ANGLE || mode_id == DIAMOND_BRACKETS)
		open_infile(file, &files->in);
	else if (mode_id == FT_TRUNCATE || mode_id == FT_APPEND)
		open_outfile(file, &files->out, mode_id);
	else if (mode_id == HERE_DOC)
		files->in = handle_here_doc(file);
}

/*
	i keeps trtack of how many chars need to be
	replaced by spaces
*/
int	open_file(char *file_name_ptr, t_files *files, int redirection_id)
{
	char	buffer[BUFFER_SIZE];
	int		i;

	ft_bzero(buffer, BUFFER_SIZE);
	if (is_multi_angled_bracket(redirection_id))
		file_name_ptr += 1;
	file_name_ptr += 1;
	i = count_consecutive_spaces(file_name_ptr);
	i += get_file_name_and_length(&buffer[0], &file_name_ptr[i]);
	open_in_mode((const char *)buffer, files, redirection_id);
	// printf("opened file: |%.*s|\nIncrementing with: %d\n",i, file_name_ptr, i);
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
		// printf("%s\n", &cursor[index]);
		redirect_id = get_redirect_id(&cursor[index]);
		length = open_file(&cursor[index], &fd, redirect_id);
		if (is_multi_angled_bracket(redirect_id))
			++length;
		replace_redirection_w_space(input, length, index);
		index += get_set_index(&cursor[index], "><");
	}
	return (fd);
}
