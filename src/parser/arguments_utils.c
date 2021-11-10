#include <parser/arguments_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <libft.h>
#include <parser/arguments.h>
#include <parser/parser.h>

void	populate_buffer_with_expanded_value(t_arg *arg, t_buffer *buffer)
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
		else if (*arg->start == VARIABLE_TOKEN && (arg->start + 1)
			!= arg->end && !ft_isspace(*(arg->start + 1)))
			++(arg->start);
		else
			append_char_to_buffer(&arg->start, buffer);
	}
}

void	copy_string_to_buffer(const char **str, t_buffer *buffer)
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

char	*get_substring(const char **str)
{
	t_buffer	buffer;
	char		*split;

	init_buffer(&buffer);
	copy_string_to_buffer(str, &buffer);
	split = ft_strdup(&buffer.buf[0]);
	if (split == NULL)
		return (NULL);
	return (split);
}

char	**split(char **splits, const char *str, int n_splits)
{
	int	i;

	i = 0;
	while (i < n_splits)
	{
		skip_spaces(&str);
		splits[i] = get_substring(&str);
		if (splits[i] == NULL)
		{
			destroy_split_arg(splits);
			return (NULL);
		}
		i++;
	}
	splits[i] = NULL;
	return (splits);
}

int	count_num_of_splits(char const *str)
{
	t_quotes_index	quotes;
	int				num_of_splits;
	int				i;

	i = 0;
	num_of_splits = 0;
	if (!ft_isspace(str[0]) && str[0] != '\0')
		num_of_splits++;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]))
		{
			quotes = get_quotes_indexes(&str[i]);
			i += quotes.end;
		}
		if (ft_isspace(str[i]) && !ft_isspace(str[i + 1]) && str[i + 1] != '\0')
			num_of_splits++;
		++i;
	}
	return (num_of_splits);
}
