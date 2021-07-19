#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// only echo = \n
// if in inverted commas printf white space trim inverted commas though
// if no inverted commas remove trim all white space including between words

// possible string
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string follow by pipe (|)    )

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	char		*substring;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char*)s;
	substring = (char*)calloc((len + 1), sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len && str[i] != '\0' && start < strlen(s))
	{
		substring[i] = str[i + start];
		i++;
	}
	return (substring);
}

int	get_substr_len(const char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (i);
		i++;
	}
	return (0);
}

char	*format_string(const char *input)
{	
	const int	sub_str_len = get_substr_len(input);
	char *str_to_return;

	str_to_return = ft_substr(input, 0, sub_str_len);
	if (str_to_return)
		str
	// const int	str_len = strlen(input);

	return (ft_substr(input, 0, sub_str_len));
}

int	echo_command(const char **input)
{
	const char	*str_to_write = format_string(*input);
	const int	len = strlen(*input);
	write(1, str_to_write, len);
	write(1, "\n", 1);
	return (1);
}
