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
		if (quotes.is_double_quote && is_env_variable(*start))
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
		else
			append_char_to_buffer(&arg->start, buffer);
    }
}

static char     **split(char **splits, const char *str, int n_splits)
{
        int i;
        int cur_len;
	
        i = 0;
        while (i < n_splits)
        {
			cur_len = 0;
			skip_spaces(&str);
			if (is_quote(*str))
			{
				t_quotes_index quotes = get_quotes_indexes(str);
				cur_len = (quotes.end + 1) - quotes.start;
			}
			else
			{
				while (str[cur_len])
				{
					if (is_quote(str[cur_len]))
					{
						t_quotes_index quotes = get_quotes_indexes(&str[cur_len]);
						cur_len += (quotes.end + 1) - quotes.start;
					}
					if (ft_isspace(str[cur_len]))
						break ;
					++cur_len;
				}
			}
			splits[i] = (char*)malloc(cur_len + 1 * sizeof(char));
			if (splits[i] == NULL)
			{
					destroy_splited_arg(splits);
					return (NULL);
			}
			ft_memcpy(splits[i], str, cur_len);
			splits[i][cur_len] = '\0';
			str = &str[cur_len];
			i++;
        }
        if (n_splits != 0)
                splits[i] = NULL;
        return (splits);
}

static int	num_of_splits(char const *str)
{
	int i;
	int num_of_splits;
	
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

char            **ft_split_on_space(char const *s)
{
        char    **split_strs;
        int             n_of_splits;

        if (s == NULL)
                return (NULL);
        n_of_splits = num_of_splits(s);
        split_strs = (char**)malloc((n_of_splits + 1) * sizeof(char*));
        if (split_strs == NULL)
                return (NULL);
        if (n_of_splits == 0 || s[0] == '\0')
        {
                split_strs[0] = NULL;
                return (split_strs);
        }
        split_strs = split(split_strs, s, n_of_splits);
        return (split_strs);
}

char **split_command_args(t_arg arg)
{
    t_buffer buffer;

    populate_buffer_with_expanded_value(&arg, &buffer);

    char **args = ft_split_on_space(&buffer.buf[0]);
    return (args);
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