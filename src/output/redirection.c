#include <output/redirection.h>
#include <output/run_commands.h>
#include <../libft/libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

void	get_files(int fd[2], t_files *files)
{
	char	file_name[BUFSIZ];

	fd[READ_FD] = -1;
	fd[WRITE_FD] = -1;
	if (files->in)
	{
		get_file_name(&file_name[0], files->in);
		fd[READ_FD] = open(&file_name[0], O_RDONLY);
		if (fd[READ_FD] == -1)
			handle_errors(11, "opening infile");
	}
	if (files->out)
	{
		ft_bzero(&file_name[0], BUFSIZ);
		get_file_name(&file_name[0], files->out);
		fd[WRITE_FD] = open(&file_name[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd[WRITE_FD] == -1)
			handle_errors(11, "opening out");
	}
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, t_files *files)
{	
	int	fd[2];

	get_files(fd, files);
	if (fd[READ_FD] != -1)
	{
		set_stdin(fd[READ_FD]);
		close(fd[READ_FD]);
	}
	else if (process != FIRST_PROCESS)
		set_stdin(pipes->previous[READ_FD]);
	if (fd[WRITE_FD] != -1)
	{
		set_stdout(fd[WRITE_FD]);
		close(fd[WRITE_FD]);
	}
	else if (process != last_process - 1)
		set_stdout(pipes->current[WRITE_FD]);
	close(pipes->current[READ_FD]);
	if (process != FIRST_PROCESS)
		close(pipes->previous[WRITE_FD]);
}
