#include <defines.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/commands.h>
#include <env/environment.h>
#include <executor/run_commands.h>

static void	update_env_value(const char *key, const char *new_value)
{
	export(get_environment(), key);
	free(find_variable(get_environment(), key)->value);
	find_variable(get_environment(), key)->value = ft_strdup(new_value);
}

static void	update_env(char *cwd_bef_cd)
{
	char	cwd_after_cd[BUFFER_SIZE];

	getcwd(cwd_after_cd, BUFFER_SIZE);
	update_env_value("OLDPWD=", cwd_bef_cd);
	update_env_value("PWD=", cwd_after_cd);
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
	char		cwd_before_cd[BUFFER_SIZE];
	t_buffer	buffer;

	(void)output;
	if (!getcwd(cwd_before_cd, BUFFER_SIZE))
		printf("FAILLLED: %s\n", cwd_before_cd);
	
	init_buffer(&buffer);
	if (command.arg.len == 0 || *command.arg.start == '~')
		copy_home_var_to_buffer(buffer.buf);
	else
	{
		while (command.arg.start < command.arg.end)
			append_expanded_input_to_buffer(&command.arg, &buffer);
	}
	if (chdir(buffer.buf) == SYS_ERROR)
	{
		if (buffer.buf[0])
			printf("cd: %s: No such file or directory\n", buffer.buf);
		return (ERROR);
	}
	update_env(cwd_before_cd);
	return (SUCCESS);
}
