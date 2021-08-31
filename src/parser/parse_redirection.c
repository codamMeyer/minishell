#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>

static void	consume_pipe(const char **input, int index)
{
	if (index < 1)
		return ;
	if (ft_strncmp("|", *input, 1) == 0)
		++(*input);
}

void init_files(t_files *files)
{
	files->in = NULL;
	files->out = NULL;
}

void	get_in_out_file(const char **input_ptr, const char id, t_files *files)
{
	int		file_name_length;

	++(*input_ptr);
	skip_spaces(input_ptr);
	file_name_length = get_cmd_len(*input_ptr);
	if (id == LEFT_ANGLE)
		files->in = *input_ptr;
	else if (id == RIGHT_ANGLE)
		files->out = *input_ptr;
	*input_ptr += file_name_length;
}

t_files get_redirection(const char **input_ptr, int index)
{
	t_files	files;

	skip_spaces(input_ptr);
	init_files(&files);
	if (**input_ptr == PIPE)
	{
		consume_pipe(input_ptr, index);
		return (files);
	}
	if (**input_ptr == LEFT_ANGLE || **input_ptr == RIGHT_ANGLE)
		get_in_out_file(input_ptr, **input_ptr, &files);
	return (files);
}