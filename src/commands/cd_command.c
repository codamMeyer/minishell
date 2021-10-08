#include <defines.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/commands.h>
#include <env/environment.h>
#include <executor/run_commands.h>

static void	update_env(char *cwd_bef_cd)
{
	char	cwd_after_cd[BUFFER_SIZE];

	getcwd(cwd_after_cd, BUFFER_SIZE);
	export(get_environment(), "OLDPWD=");
	export(get_environment(), "PWD=");
	find_variable(get_environment(), "OLDPWD")->value = ft_strdup(cwd_bef_cd);
	find_variable(get_environment(), "PWD")->value = ft_strdup(cwd_after_cd);
}

static void	copy_home_var_to_buffer(char *buffer)
{
	const t_env	*home_var = find_variable(get_environment(), "HOME");
	int			len;

	if (!home_var)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	len = ft_strlen(home_var->value) + 1;
	ft_strlcpy(buffer, home_var->value, len);
}

t_exit_code	cd_command(t_command command, t_output_stdout output)
{
	char		buffer[BUFFER_SIZE];
	char		cwd_before_cd[BUFFER_SIZE];

	(void)output;
	getcwd(cwd_before_cd, BUFFER_SIZE);
	if (command.arg.len == 0 || *command.arg.start == '~')
		copy_home_var_to_buffer(buffer);
	else
		ft_strlcpy(buffer, command.arg.start, command.arg.len + 1);
	if (chdir(buffer) == SYS_ERROR)
		return (ERROR);
	update_env(cwd_before_cd);
	return (SUCCESS);
}
