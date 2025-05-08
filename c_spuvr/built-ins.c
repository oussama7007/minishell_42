/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:01 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/08 16:38:00 by oadouz           ###   ########.fr       */
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

static int	change_directory(char *target_dir, char *curr_dir,
							char ***env_ptr, char **args)
{
	char	new_dir[1024];

	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(args[1]);
		return (1);
	}
	if (!getcwd(new_dir, sizeof(new_dir)))
		return (perror("minishell: cd"), 1);
	my_setenv("OLDPWD", curr_dir, env_ptr);
	my_setenv("PWD", new_dir, env_ptr);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		printf("%s\n", new_dir);
	return (0);
}

int	ft_cd(char **args, char ***env_ptr)
{
	char	*target_dir;
	char	curr_dir[1024];

	if (!getcwd(curr_dir, sizeof(curr_dir)))
		return (perror("minishell: cd"), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		target_dir = my_getenv("HOME", *env_ptr);
	else if (ft_strcmp(args[1], "-") == 0)
		target_dir = my_getenv("OLDPWD", *env_ptr);
	else
		target_dir = args[1];
	if (!target_dir)
		return (ft_putstr_fd("minishell: cd: path not set\n", 2), 1);
	return (change_directory(target_dir, curr_dir, env_ptr, args));
}
