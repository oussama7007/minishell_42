#include "../built_functions.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

char	*determine_target_path(char **args, char **envp,
							int *must_free_target)
{
	char	*path;

	*must_free_target = 0;
	if (!args[1] || args[1][0] == '\0')
	{
		path = my_getenv("HOME", envp);
		if (!path || path[0] == '\0')
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(path);
			return (NULL);
		}
		*must_free_target = 1;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = my_getenv("OLDPWD", envp);
		if (!path || path[0] == '\0')
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			free(path);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
		*must_free_target = 1;
	}
	else
		path = args[1];
	return (path);
}

static char	*join_logical_pwd(const char *base, const char *arg)
{
	char	*tmp;
	char	*result;
	size_t	base_len;

	if (!arg)
		return (ft_strdup(base));
	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (!base || base[0] == '\0')
		return (ft_strdup(arg));
	base_len = ft_strlen(base);
	if (base_len > 0 && base[base_len - 1] == '/')
	{
		result = ft_strjoin(base, arg);
		return (result);
	}
	tmp = ft_strjoin(base, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, rel);
	free(tmp);
	return (result);
}

void	update_environment_after_cd(char *old_pwd_val,
									const char *target_path_arg,
									char ***env_ptr)
{
	char	*new_physical_pwd;
	char	*new_logical_pwd_val;

	if (old_pwd_val)
		my_setenv("OLDPWD", old_pwd_val, env_ptr);
	new_physical_pwd = getcwd(NULL, 0);
	if (new_physical_pwd)
	{
		my_setenv("PWD", new_physical_pwd, env_ptr);
		free(new_physical_pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		new_logical_pwd_val = join_logical_pwd(old_pwd_val, target_path_arg);
		if (new_logical_pwd_val)
		{
			my_setenv("PWD", new_logical_pwd_val, env_ptr);
			free(new_logical_pwd_val);
		}
	}
}