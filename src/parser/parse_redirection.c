#include <commands/commands.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
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

	ft_bzero(&buffer[0], BUFSIZ);
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

/*
	Might still split this into diff functions
*/
void	open_in_mode(const char *file, t_files *files, int mode_id)
{
	if (mode_id == LEFT_ANGLE)
	{
		if (files->in > 0)
			close(files->in);
		files->in = open(file, O_RDONLY, 0644);
		if (files->in == -1)
		{
			printf("Couldn't open in file: %s\n", file);
			exit(1);
		}
	}
	else if (mode_id == RIGHT_ANGLE)
	{
		if (files->out > 0)
			close(files->out);
		files->out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (files->out == -1)
		{
			printf("Couldn't open out file:%s\n", file);
			exit(1);
		}
	}
}

/*
	i keeps trtack of how many chars need to be
	replaced by spaces
*/
int	open_file(char *file_name_ptr, t_files *files, int redirection_id)
{
	char	buffer[BUFSIZ];
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
	int		char_id;
	t_files	fd;
	char	*cursor;

	fd.in = -1;
	fd.out = -1;
	cursor = *input;
	index = get_arg_len(&cursor[0], "><") + 1;
	while (index < string_to_parse_len)
	{
		char_id = cursor[index - 1];
		length = open_file(&cursor[index], &fd, char_id);
		replace_redirection_w_space(input, length + 1, index - 1);
		index += get_arg_len(&cursor[index], "><") + 1;
	}
	return (fd);
}
