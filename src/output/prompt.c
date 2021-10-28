#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/pwd_command_utils.h>
#include <env/environment.h>
#include <output/prompt.h>

#define COLOR "\e[1;36m"
#define RED "\e[0;31m"
#define RESET_COLOR " -► \e[0m "

char	*display_prompt(char *buffer)
{
	const int	color_len = ft_strlen(COLOR) + 1;
	const int	reset_color_len = ft_strlen(RESET_COLOR);
	t_buffer	path;
	int			path_len;

	init_buffer(&path);
	ft_bzero(buffer, sizeof(buffer));
	if (!get_pwd(path.buf))
	{
		ft_strlcpy(buffer, RED, color_len);
		ft_strlcpy(&buffer[ft_strlen(buffer)], "WHY THOUGH???", 14);
		return (buffer);
	}
	path_len = ft_strlen(path.buf) + 1;
	ft_strlcpy(buffer, COLOR, color_len);
	ft_strlcpy(&buffer[ft_strlen(buffer)], path.buf, path_len);
	ft_strlcpy(&buffer[ft_strlen(buffer)], RESET_COLOR, reset_color_len);
	return (buffer);
}
