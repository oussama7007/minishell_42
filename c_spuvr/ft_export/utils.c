/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:26:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 17:06:41 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

void	print_err_111(const char *arg_part)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd((char *)arg_part, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	free_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	if (!env_copy)
		return ;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

int	is_valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || name[0] == '\0' || (!ft_isalpha(name[i]) && name[i] != '_'))
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*build_appended_value(const char *old_val, const char *val_to_append)
{
	if (!old_val)
		return (ft_strdup(val_to_append));
	return (ft_strjoin(old_val, val_to_append));
}
