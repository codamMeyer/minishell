#include <stdio.h>
#include <output/prompt.h>
#include <unistd.h>
#include <libft.h>
#define COLOR "\e[1;36m "
#define RESET_COLOR " -►\e[0m  "

char	*display_prompt(char *buffer)
{
	const char	*path = getcwd(NULL, 0);
	const int	path_len = ft_strlen(path) + 1;
	const int	color_len = ft_strlen(COLOR);
	const int	reset_color_len = ft_strlen(RESET_COLOR);

	ft_bzero(buffer, sizeof(buffer));
	ft_strlcpy(buffer, COLOR, color_len);
	ft_strlcpy(&buffer[ft_strlen(buffer)], path, path_len);
	ft_strlcpy(&buffer[ft_strlen(buffer)], RESET_COLOR, reset_color_len);
	free((char *)path);
	return (buffer);
}
