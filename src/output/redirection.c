#include <output/handle_pipes.h>
#include <parser/command_table.h>
#include <../libft/libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

typedef enum e_file_id
{
	IN = 12,
	OUT = 13
}	t_file_id;

void	current_to_previous_pipe(t_multi_pipes *pipes)
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

void	get_file_name(char *dst_buffer, const char *src)
{
	const int	file_name_len = get_cmd_len(src);

	ft_strlcpy(dst_buffer, src, file_name_len + 1);
}

void	get_files(int fd[2], t_files *files)
{
	char	file_name[BUFSIZ];

	fd[READ_FD] = -1;
	fd[WRITE_FD] = -1;
	if (files->in)
	{
		get_file_name(&file_name[0], files->in);
		printf("in: |%s|\n", file_name);
		fd[READ_FD] = open(&file_name[0], O_RDONLY);
		if (fd[READ_FD] == -1)
			handle_errors(11, "opening infile");
	}
	if (files->out)
	{
		ft_bzero(&file_name[0], BUFSIZ);
		get_file_name(&file_name[0], files->out);
		printf("out: |%s|\n", file_name);
		fd[WRITE_FD] = open(&file_name[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd[WRITE_FD] == -1)
			handle_errors(11, "opening infile");
	}
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, t_files *files)
{	
	int	fd[2];

	get_files(fd, files);
	if (fd[READ_FD] != -1)
	{
		write(2, "setting input to file!\n", 24);
		set_stdin(fd[READ_FD]);
		close(fd[READ_FD]);
	}
	else if (process != FIRST_PROCESS)
		set_stdin(pipes->previous[READ_FD]);
	if (fd[WRITE_FD] != -1)
	{
		write(2, "setting output to file!\n", 25);
		set_stdout(fd[WRITE_FD]);
		close(fd[WRITE_FD]);
	}
	else if (process != last_process - 1)
		set_stdout(pipes->current[WRITE_FD]);
	close(pipes->current[READ_FD]);
	if (process != FIRST_PROCESS)
		close(pipes->previous[WRITE_FD]);
}
