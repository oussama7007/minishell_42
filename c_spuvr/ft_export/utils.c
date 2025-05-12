/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:26:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/12 16:28:04 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

void	print_err_111(const char *arg_part)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg_part, STDERR_FILENO);
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

