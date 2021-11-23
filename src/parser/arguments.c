#include <parser/arguments.h>

#include <libft.h>
#include <parser/parser.h>
#include <parser/arguments_utils.h>

char	**split_args_on_spaces(char const *str)
{
	char	**split_strs;
	int		n_of_splits;

	if (str == NULL)
		return (NULL);
	n_of_splits = count_num_of_splits(str);
	split_strs = (char **)malloc((n_of_splits + 1) * sizeof(char *));
	if (split_strs == NULL)
		return (NULL);
	return (split(split_strs, str, n_of_splits));
}

char	**split_command_args(t_arg arg)
{
	t_buffer	buffer;

	populate_buffer_with_expanded_value(&arg, &buffer);
	return (split_args_on_spaces(&buffer.buf[0]));
}

void	destroy_split_arg(char **args)
{
	int	i;

	i = 0;
	while (args && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}
