#include <output/write_to_std.h>
#include <libft.h>

void	write_to_stdout(const char *string_to_write)
{
	int	len_inside;
	
	if (!string_to_write)
		return ;
	len_inside = ft_strlen(string_to_write);
	write(STDOUT_FILENO, string_to_write, len_inside);
}

void	write_to_stderr(const char *string_to_write)
{
	int	len_inside;
	
	if (!string_to_write)
		return ;
	len_inside = ft_strlen(string_to_write);
	write(STDERR_FILENO, string_to_write, len_inside);
}
