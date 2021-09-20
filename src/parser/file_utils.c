#include <fcntl.h>
#include <parser/parse_redirection.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

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

void	open_outfile(const char *file, int *out_file, t_bool should_append)
{
	if (*out_file != INVALID_FD)
		close(*out_file);
	if (should_append == APPEND)
	{
		// printf("Openingn in Append mode!!!\n");
		*out_file = open(file, O_RDWR | O_CREAT | O_APPEND, 0664);
	}
	else
	{
		// printf("Openingn in truncate mode!!!\n");
		*out_file = open(file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	}
	if (*out_file == INVALID_FD)
	{
		printf("Couldn't open in file: %s\n", file);
		exit(1);
	}
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