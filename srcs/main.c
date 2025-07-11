/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:26:38 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 21:15:04 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

int	main(int ac, char **av, char **env)
{
	char	**my_envp;
	t_data	data;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	(void)ac;
	(void)av;
	my_envp = init_environment(env);
	ensure_minimal_env(&my_envp);
	data = (t_data){0};
	main_loop(&my_envp, &data);
	free_environment(my_envp);
	return (data.ex_status);
}
