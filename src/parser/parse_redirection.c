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

// void	init_files(t_files *files)
// {
// 	files->in = NULL;
// 	files->out = NULL;
// }

// /*
// 	Points to files name and consumes that part of the user input string
// */
// void	get_in_out_file(const char **input_ptr, const char id, t_files *files)
// {
// 	++(*input_ptr);
// 	skip_spaces(input_ptr);
// 	if (id == LEFT_ANGLE)
// 		files->in = *input_ptr;
// 	else if (id == RIGHT_ANGLE)
// 		files->out = *input_ptr;
// 	*input_ptr += get_cmd_len(*input_ptr);
// }

/*
	Creates a struct with two char pointers to the name of the files.
	TODO: Check if file is valid with fstat
	< infile cmd1 < infile2
	if multiple infile, take the last one
	if any of the multiple infiles is invalid, point to the invalid file.
	check <>, >< filename
*/

// void get_file_name(char *buffer, char *input_ptr)
// {
// 	const int	len = get_cmd_len(input_ptr);
// 	ft_strlcpy(&buffer[0], input_ptr, len + 1);
// 	input_ptr += len;
// }
