#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/pwd_command_utils.h>
#include <env/environment.h>
#include <output/prompt.h>

#define BLUE "\e[0;36m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"

#define RED_ARROW "\e[1;31m -► \e[0m "
#define GREEN_ARROW "\e[1;32m -► \e[0m "

char	*display_prompt(char *buffer)
{
	const int	color_len = ft_strlen(BLUE) + 1;
	const int	reset_ok_len = ft_strlen(RED_ARROW);
	const int	reset_error_len = ft_strlen(GREEN_ARROW);
	t_buffer	path;
	int			path_len;

	init_buffer(&path);
	ft_bzero(buffer, sizeof(buffer));
	if (!get_pwd(path.buf))
	{
		ft_strlcpy(buffer, RED, color_len);
		ft_strlcpy(&buffer[ft_strlen(buffer)], "WHY THOUGH???", 14);
		ft_strlcpy(&buffer[ft_strlen(buffer)], RED_ARROW, reset_error_len);
		return (buffer);
	}
	path_len = ft_strlen(path.buf) + 1;
	ft_strlcpy(buffer, BLUE, color_len);
	ft_strlcpy(&buffer[ft_strlen(buffer)], path.buf, path_len);
	if (*(get_exit_code()) != SUCCESS)
		ft_strlcpy(&buffer[ft_strlen(buffer)], RED_ARROW, reset_error_len);
	else
		ft_strlcpy(&buffer[ft_strlen(buffer)], GREEN_ARROW, reset_ok_len);
	return (buffer);
}
