/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:44 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 15:27:45 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

// to valid identifier
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

// print variables sorted
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
