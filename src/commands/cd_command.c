#include <defines.h>
#include <libft.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/commands.h>
#include <env/environment.h>
#include <executor/run_commands.h>

static void	update_env_value(const char *key, const char *new_value)
{
	t_env	*var;
	char	*args[3];

	args[0] = NULL;
	args[1] = (char *)key;
	args[2] = NULL;

	export(get_environment(), args);
	var = find_variable(get_environment(), key);
	free(var->value);
	var->value = ft_strdup(new_value);
	if (!var->value)
		handle_error(MALLOC_ERROR, NULL, "malloc()");
}

static void	update_env(char *cwd_bef_cd)
{
	char	cwd_after_cd[BUFFER_SIZE];

	getcwd(cwd_after_cd, BUFFER_SIZE);
	update_env_value("OLDPWD=", cwd_bef_cd);
	update_env_value("PWD=", cwd_after_cd);
}

static t_exit_code	copy_home_var_to_buffer(char *buffer)
{
	const t_env	*home_var = find_variable(get_environment(), "HOME");
	int			len;

	if (!home_var)
	{
		handle_error(HOME_NOT_SET_ERROR, "cd: ", NULL);
		return (ERROR);
	}
	len = ft_strlen(home_var->value) + 1;
	ft_strlcpy(buffer, home_var->value, len);
	return (SUCCESS);
}

t_exit_code	cd_command(t_command command, t_output_stdout output)
{
	char		cwd_before_cd[BUFFER_SIZE];
	t_buffer	buffer;
	t_exit_code	ret;

	(void)output;
	ret = SUCCESS;
	getcwd(cwd_before_cd, BUFFER_SIZE);
	init_buffer(&buffer);
	if (!command.arguments[1] || !ft_strcmp(command.arguments[1], "~"))
		ret = copy_home_var_to_buffer(buffer.buf);
	else
		ft_strlcpy(buffer.buf, command.arguments[1], ft_strlen(command.arguments[1]) + 1);
	if (chdir(buffer.buf) == SYS_ERROR && ret == SUCCESS)
	{
		handle_error(SYS_ERROR, "cd", buffer.buf);
		ret = ERROR;
	}
	update_env(cwd_before_cd);
	return (ret);
}
