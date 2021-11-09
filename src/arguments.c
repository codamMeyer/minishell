#include <arguments.h>
#include <stdlib.h>
#include <commands/buffer.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <commands/quotes.h>
#include <parser/command_table.h>
#include <defines.h>
#include <libft.h>
#include <parser/parser.h>

static void	append_env_value_to_buffer(const char **start, t_buffer *buffer)
{
	const t_env	*var = find_variable(get_environment(), *start);
	const int	key_len = get_key_len(*start);

	if (var)
	{
		ft_strlcpy(&buffer->buf[buffer->index], var->value, ft_strlen(var->value) + 1);
		buffer->index += ft_strlen(var->value);
	}
	*start = *start + key_len;
}

static void	append_quoted_string_to_buffer(const char **start, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(*start);

	*start = quotes.start - 1;
	while (*start <= quotes.end)
	{
		if (quotes.is_double_quote && (is_env_variable(*start)))
		{
			++(*start);
			append_env_value_to_buffer(start, buffer);
		}
		else
			append_char_to_buffer(start, buffer);
	}
}

static void    populate_buffer_with_expanded_value(t_arg *arg, t_buffer *buffer)
{
	init_buffer(buffer);    
	while (arg->start < arg->end)
	{
		if (is_quote(*arg->start))
			append_quoted_string_to_buffer(&arg->start, buffer);
		else if (is_env_variable(arg->start))
		{
			++(arg->start);
			append_env_value_to_buffer(&arg->start, buffer);
		}
		else if (ft_strncmp(arg->start, "$?", 2) == 0)
			append_exit_code_to_buffer(&arg->start, buffer);
		else if (*arg->start == VARIABLE_TOKEN && (arg->start + 1) != arg->end && !ft_isspace(*(arg->start + 1)))
			++(arg->start);
		else
			append_char_to_buffer(&arg->start, buffer);
	}
}

static void	copy_string_to_buffer(const char **str, t_buffer *buffer)
{
	t_quotes_index	quotes;
	int				quotes_len;

	while (*str && *(*str))
	{
		if (is_quote(*(*str)))
		{
			quotes = get_quotes_indexes(*str);
			quotes_len = quotes.end - quotes.start;
			++(*str);
			ft_strlcpy(&buffer->buf[buffer->index], *str, quotes_len);
			buffer->index += quotes_len - 1;
			(*str) += quotes_len;
		}
		if (ft_isspace(*(*str)))
			break ;
		buffer->buf[buffer->index] = *(*str);
		++buffer->index;
		++(*str);
	}
}

static char	*get_substring(const char **str)
{
	t_buffer buffer;
	char *split;

	init_buffer(&buffer);
	copy_string_to_buffer(str, &buffer);
	split = ft_strdup(&buffer.buf[0]);
	if (split == NULL)
		return (NULL);
	return (split);
}


static char     **split(char **splits, const char *str, int n_splits)
{
	int i;

	i = 0;
	while (i < n_splits)
	{
		skip_spaces(&str);
		splits[i] = get_substring(&str);
		if (splits[i] == NULL)
		{
			destroy_splited_arg(splits);
			return (NULL);
		}
		i++;
	}
	splits[i] = NULL;
	return (splits);
}

static int	count_num_of_splits(char const *str)
{
	int num_of_splits;
	int i;
	
	i = 0;
	num_of_splits = 0;
	if (!ft_isspace(str[0]) && str[0] != '\0')
		num_of_splits++;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]))
		{
			t_quotes_index quotes = get_quotes_indexes(&str[i]);
			i += quotes.end;
		}
		if (ft_isspace(str[i]) && !ft_isspace(str[i + 1]) && str[i + 1] != '\0')
			num_of_splits++;
		++i;
	}
	return (num_of_splits);
}

char            **split_args_on_spaces(char const *str)
{
	char	**split_strs;
	int		n_of_splits;

	if (str == NULL)
		return (NULL);
	n_of_splits = count_num_of_splits(str);
	split_strs = (char**)malloc((n_of_splits + 1) * sizeof(char*));
	if (split_strs == NULL)
			return (NULL);
	return (split(split_strs, str, n_of_splits));
}

char **split_command_args(t_arg arg)
{
	t_buffer buffer;

	populate_buffer_with_expanded_value(&arg, &buffer);
	return (split_args_on_spaces(&buffer.buf[0]));
}

void    destroy_splited_arg(char **args)
{
	int i = 0;
	while (args && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}