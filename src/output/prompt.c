#include <libft.h>
#include <commands/pwd_command_utils.h>
#include <env/environment.h>
#include <output/prompt.h>

#define BLUE "\e[0;36m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define RED_ARROW "\e[1;31m -► "
#define GREEN_ARROW "\e[1;32m -► "
#define RESET "\e[0m "

static void	copy_prompt_to_buffer(t_buffer path, char *prompt_buffer)
{
	const int	path_len = ft_strlen(path.buf) + 1;
	const int	color_len = ft_strlen(BLUE) + 1;

	ft_strlcpy(prompt_buffer, BLUE, color_len);
	ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], path.buf, path_len);
}

static void	copy_symbol_to_buffer(char *prompt_buffer)
{
	const t_bool	is_success = (*(get_exit_code()) == SUCCESS);
	const int		green_len = ft_strlen(GREEN_ARROW) + 1;
	const int		red_len = ft_strlen(RED_ARROW) + 1;
	const int		reset_len = ft_strlen(RESET);

	if (is_success)
		ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], \
											GREEN_ARROW, green_len);
	else
		ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], \
											RED_ARROW, red_len);
	ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], RESET, reset_len);
}

static void	copy_error_message_to_prompt(char *prompt_buffer)
{
	const int		red_len = ft_strlen(RED_ARROW) + 1;
	const int		reset_len = ft_strlen(RESET);

	ft_strlcpy(prompt_buffer, RED, red_len);
	ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], "WHY THOUGH???", 14);
	ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], RED_ARROW, red_len);
	ft_strlcpy(&prompt_buffer[ft_strlen(prompt_buffer)], RESET, reset_len);
}

char	*display_prompt(char *buffer)
{
	t_buffer	path;

	init_buffer(&path);
	ft_bzero(buffer, sizeof(buffer));
	if (!get_pwd(path.buf))
	{
		copy_error_message_to_prompt(buffer);
		return (buffer);
	}
	copy_prompt_to_buffer(path, buffer);
	copy_symbol_to_buffer(buffer);
	return (buffer);
}
