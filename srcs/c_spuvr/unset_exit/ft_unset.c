/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:39 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/25 19:35:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../built_functions.h"

static int process_unset_arg(char *arg, char ***env_ptr)
{
	if (!arg || !env_ptr || !(*env_ptr))
		return (0);
	
	my_unsetenv(arg, env_ptr);
	return (0);
}

/*
** Unset one or more environment variables
** Returns 0 on success (always succeeds, bash-like)
*/
int	ft_unset(char **args, char ***env_ptr)
{
	int	i;

	if (!args || !env_ptr || !(*env_ptr))
		return (0);
	
	i = 1;
	while (args[i])
	{
		process_unset_arg(args[i], env_ptr);
		i++;
	}
	
	return (0); // Will be 0 since process_unset_arg always returns 0
}


// #include "../built_functions.h"

// static int process_unset_arg(t_head_list *head, char *arg, char ***env_ptr)
// {
// 	if (!arg || !env_ptr || !(*env_ptr))
// 		return (0);
	
// 	my_unsetenv(head,arg, env_ptr);
// 	return (0);
// }

// /*
// ** Unset one or more environment variables
// ** Returns 0 on success (always succeeds, bash-like)
// */
// int	ft_unset(t_head_list *head, char **args, char ***env_ptr)
// {
// 	int	i;

// 	if (!args || !env_ptr || !(*env_ptr))
// 		return (0);
	
// 	i = 1;
// 	while (args[i])
// 	{
// 		process_unset_arg(head, args[i], env_ptr);
// 		i++;
// 	}
	
// 	return (0); // Will be 0 since process_unset_arg always returns 0
// }
