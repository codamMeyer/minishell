#include <commands/commands.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <stdio.h>

void	skip_redirection(const char **input_ptr)
{
	skip_spaces(input_ptr);
	while (**input_ptr == LEFT_ANGLE || **input_ptr == RIGHT_ANGLE)
	{
		++(*input_ptr);
		skip_spaces(input_ptr);
		*input_ptr += get_cmd_len(*input_ptr);
		skip_spaces(input_ptr);
	}
}

void	check_cmd_str_validity(char *cmd_str)
{
	int	i;

	i = 0;
	while (cmd_str && cmd_str[i])
	{
		if (cmd_str[i] == DOUBLE_QUOTES)
		{
			i++;
			while (cmd_str[i] && cmd_str[i] != DOUBLE_QUOTES)
				i++;
		}
		if (i > 0 && cmd_str[i + 1] == RIGHT_ANGLE && cmd_str[i] != SPACE)
			handle_errors(16, "Syntax error in checker for outfile");
		i++;
	}
}

int	count_consecutive_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == SPACE)
		i++;
	return (i);
}

int		get_file_name_and_length(char *buffer, char *input)
{
	const int	file_name_len = get_arg_len(input, SPECIALS);
	int			len_to_cpy;

	ft_bzero(&buffer[0], BUFSIZ);
	if (*input == DOUBLE_QUOTES)
	{
		++(input);
		len_to_cpy = file_name_len - 2;
	}
	else
		len_to_cpy = file_name_len;
	ft_strlcpy(&buffer[0], input, len_to_cpy + 1);
	return (file_name_len);
}

// void	handle_infile(char **file_name_ptr, int *in_file)
// {
// 	char	buffer[BUFSIZ];
// 	int		fd;
// 	int		i;

// 	i = count_consecutive_spaces(*file_name_ptr);
// 	get_file_name(&buffer[0], file_name_ptr);
// 	fd = open(buffer, O_RDONLY, 0644);
// 	if (fd == SYS_ERROR)
// 		handle_errors(SYS_ERROR, "handle_infile_open");
// 	if (dup2(fd, STDIN_FILENO) == SYS_ERROR)
// 		handle_errors(SYS_ERROR, "handle_infile_dup2");
// 	*in_file = fd;
// 	close(fd);
// }

// int	get_files_descriptors(char *input, t_files *fd)
// {

// 	if (*input == LEFT_ANGLE)
// 		// return(handle_infile(&input, &fd->in));
// 	if (*input == RIGHT_ANGLE)
// 		return(handle_outfile(&input, &fd->out));
// }

/*
	return t_files which have an int for the in and out fd's respectively
*/

t_files	get_redirection(char **input)
{
	const int	string_to_parse_len = get_arg_len(*input, "|");
	int			redirection_index;
	// int			redirection_length;
	t_files		fd;
	char *cursor = *input;

	fd.in = -1;
	fd.out = -1;
	// redirection_index = get_arg_len(&(*input[0]), "><");
	redirection_index = get_arg_len(&cursor[0], "><") + 1;
	while (redirection_index < string_to_parse_len && cursor[redirection_index])
	{
		// redirection_length = get_files_descriptors(&cursor[redirection_index], &fd);
		redirection_index += get_arg_len(&cursor[redirection_index], "><") + 1;
	}
	return (fd);
}

// echo halla > out