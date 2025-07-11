/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 02:24:47 by oadouz            #+#    #+#             */
/*   Updated: 2025/07/11 02:24:59 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

static char	*append_string(char *dest, char *src)
{
	char	*temp;
	char	*result;

	temp = dest;
	result = ft_strjoin(temp, src);
	free(temp);
	return (result);
}

static int	process_n_option(char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (args[i] && is_nn_option(args[i]))
	{
		n_option = 1;
		i++;
	}
	return (n_option);
}

static int	skip_n_options(char **args)
{
	int	i;

	i = 1;
	while (args[i] && is_nn_option(args[i]))
		i++;
	return (i);
}

static char	*build_output_string(char **args, int start_index)
{
	char	*output_str;
	int		i;

	output_str = ft_strdup("");
	if (!output_str)
		return (NULL);
	i = start_index;
	while (args[i])
	{
		output_str = append_string(output_str, args[i]);
		if (!output_str)
			return (NULL);
		if (args[i + 1])
		{
			output_str = append_string(output_str, " ");
			if (!output_str)
				return (NULL);
		}
		i++;
	}
	return (output_str);
}

int	ft_echo(char **args)
{
	int		n_option;
	int		start_index;
	char	*output_str;

	n_option = process_n_option(args);
	start_index = skip_n_options(args);
	output_str = build_output_string(args, start_index);
	if (!output_str)
		return (1);
	if (n_option == 0)
	{
		output_str = append_string(output_str, "\n");
		if (!output_str)
			return (1);
	}
	write(STDOUT_FILENO, output_str, ft_strlen(output_str));
	free(output_str);
	return (0);
}
