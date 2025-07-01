/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:22:45 by oadouz            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/29 20:47:10 by oadouz           ###   ########.fr       */
=======
/*   Updated: 2025/06/30 11:27:54 by oait-si-         ###   ########.fr       */
>>>>>>> bf0e99ec959c40e207915c72f39fd029fdc72051
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

static int	is_numeric_arg(char *str)
{
    int	i;

    i = 0;
    if (!str || !*str)
        return (0);
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static void	cleanup_and_exit(t_data *data, char **env, t_command *cmd, t_token *tok)
{
    if (env)
        free_environment(env);
    if (cmd)
        free_command(cmd);
    if (tok)
        free_tokens(tok);
    //rl_clear_history();
    exit(data->ex_status);
}

int	ft_exit(char **args, char ***env, t_command *cmd, t_token *tok, t_data *data)
{
    //long long	exit_code;

    
    ft_putendl_fd("exit", 1);
    if (!args[1])
        cleanup_and_exit(data, *env, cmd, tok);
    if (!is_numeric_arg(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        data->ex_status = 255;
        cleanup_and_exit(data, *env, cmd, tok);
    }
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    data->ex_status = ft_atoi(args[1]);
    cleanup_and_exit(data, *env, cmd, tok);
    return (0);
}
