/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:01 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/08 16:23:20 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
#include "built_functions.h"

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		n = 1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n)
		ft_putchar_fd("\n", STDOUT_FILENO);
	return (0);
}

int	ft_cd(char **args, char ***env_ptr)
{
	char	*target_dir;
	char	curr_dir[1024];
	char	new_dir[1024];

	if (!getcwd(curr_dir, sizeof(curr_dir)))
		return (perror("minishell: cd"), 1);
	if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
		target_dir = my_getenv("HOME", *env_ptr);
	else if (ft_strn)
}
