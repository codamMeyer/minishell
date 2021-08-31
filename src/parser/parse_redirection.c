#include <commands/commands.h>
#include <parser/command_table.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <stdio.h>

void init_files(t_files *files)
{
	files->in = NULL;
	files->out = NULL;
}

void	get_in_out_file(const char **input_ptr, const char id, t_files *files)
{
	++(*input_ptr);
	skip_spaces(input_ptr);
	if (id == LEFT_ANGLE)
		files->in = *input_ptr;
	else if (id == RIGHT_ANGLE)
		files->out = *input_ptr;
	*input_ptr += get_cmd_len(*input_ptr);
}

void get_redirection(const char **input_ptr, t_files *files)
{
	
	skip_spaces(input_ptr);
	if (**input_ptr == LEFT_ANGLE || **input_ptr == RIGHT_ANGLE)
		get_in_out_file(input_ptr, **input_ptr, files);
}