#include <output/redirection.h>
#include <output/run_commands.h>
#include <libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

void	get_files(int fd[], t_files *files)
{
	char	file_name[BUFSIZ];

	fd[READ_FD] = SYS_ERROR;
	fd[WRITE_FD] = SYS_ERROR;
	if (files->in)
	{
		get_file_name(&file_name[0], files->in);
		fd[READ_FD] = open(&file_name[0], O_RDONLY);
		if (fd[READ_FD] == SYS_ERROR)
			handle_errors(11, "opening infile");
	}
	if (files->out)
	{
		ft_bzero(&file_name[0], BUFSIZ);
		get_file_name(&file_name[0], files->out);
		fd[WRITE_FD] = open(&file_name[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (fd[WRITE_FD] == SYS_ERROR)
			handle_errors(11, "opening out");
	}
}

void	handle_stdin(int in_file, t_multi_pipes *pipes, int process)
{
	if (in_file != SYS_ERROR)
	{
		set_stdin(in_file);
		close(in_file);
	}
	else if (process != FIRST_PROCESS)
		set_stdin(pipes->previous[READ_FD]);
}

void	handle_stdout(int out_file, t_multi_pipes *pipes, int process,
	int last_process)
{
	if (out_file != SYS_ERROR)
	{
		set_stdout(out_file);
		close(out_file);
	}
	else if (process != last_process - 1)
		set_stdout(pipes->current[WRITE_FD]);
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, t_files *file_names)
{	
	int	fd[2];

	get_files(fd, file_names);
	handle_stdin(fd[READ_FD], pipes, process);
	handle_stdout(fd[WRITE_FD], pipes, process, last_process);
	close(pipes->current[READ_FD]);
	if (process != FIRST_PROCESS)
		close(pipes->previous[WRITE_FD]);
}
