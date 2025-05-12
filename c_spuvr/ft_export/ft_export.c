/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 15:09:24 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

static int	is_valid_identifier(const char *name)
{
	if (!name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static void	print_export_var(char *env_var)
{
	char	*eq_ptr;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq_ptr = ft_strchr(env_var, '=');
	if (eq_ptr)
	{
		*eq_ptr = '\0';
		ft_putstr_fd(env_var, STDOUT_FILENO);
		*eq_ptr = '=';
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq_ptr + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(env_var, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_export_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		print_export_var(envp[i]);
		i++;
	}
}

void	export_print_1(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	handle_name_value(char *arg, char ***env_ptr)
{
	char	*eq_ptr;
	char	*name;
	int		status;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr == arg)
		return (export_print_1(arg), 1);
	name = ft_strdup(arg);
	if (!name)
		return (1);
	name[eq_ptr - arg] = '\0';
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(name);
		return (1);
	}
	status = my_setenv(name, eq_ptr + 1, env_ptr);
	return (free(name), status);
}

static int	handle_name_only(char *arg, char ***env_ptr)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	if (!my_getenv(arg, *env_ptr))
		my_setenv(arg, "", env_ptr);
	return (0);
}

int	ft_export(char **args, char ***env_ptr)
{
	int		i;
	int		ret_status;
	char	*eq_ptr;

	ret_status = 0;
	if (!env_ptr || !(*env_ptr))
		return (1);
	if (!args[1])
	{
		print_export_env(*env_ptr);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq_ptr = ft_strchr(args[i], '=');
		if (eq_ptr)
			ret_status |= handle_name_value(args[i], env_ptr);
		else
			ret_status |= handle_name_only(args[i], env_ptr);
		i++;
	}
	return (ret_status);
}
