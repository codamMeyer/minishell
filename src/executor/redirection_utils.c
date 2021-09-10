#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <../libft/libft.h>

void	previous_to_current_pipe(t_multi_pipes *pipes)
{
	pipes->previous[READ_FD] = pipes->current[READ_FD];
	pipes->previous[WRITE_FD] = pipes->current[WRITE_FD];
}

void	set_stdout(int new_std_out)
{
	if (dup2(new_std_out, STDOUT_FILENO) == SYS_ERROR)
		handle_errors(9, "redirect, setting child output");
}

void	set_stdin(int new_std_in)
{
	if (dup2(new_std_in, STDIN_FILENO) == SYS_ERROR)
		handle_errors(9, "redirect, setting child input");
}

// void	get_file_name(char *dst_buffer, const char *src)
// {
// 	const int	file_name_len = get_cmd_len(src);

// 	ft_strlcpy(dst_buffer, src, file_name_len + 1);
// }
