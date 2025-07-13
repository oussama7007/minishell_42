/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:53:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/13 01:46:27 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_spuvr/built_functions.h"

void	error(int type)
{
	if (type == ERR_PIPE)
		write(2, "Minishell: syntax error near unexpected token `|'\n", 50);
	else if (type == ERR_SEMICOLON)
		write(2, "Minishell: syntax error near unexpected token `;'\n", 51);
	else if (type == ERR_NEWLINE)
		write(2,
			"Minishell: syntax error near unexpected token `newline'\n", 57);
	else if (type == ERR_SYNTAX)
		write(2, "Minishell: syntax error \n", 26);
	else if (type == ERR_AMBIGUOS)
		write(2, "minishell: $...: ambiguous redirect\n", 36);
	else
		write(2, "Minishell: syntax error \n", 26);
}

int	check_single_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '\'')
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_double_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == '"')
			return (1);
		(*i)++;
	}
	return (0);
}

int	handle_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (!check_single_quotes(line, &i))
				return (0);
		}
		if (line[i] == '"')
		{
			if (!check_double_quotes(line, &i))
				return (0);
		}
	}
	return (1);
}

int	check_invalid_char(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ';' || line[i] == 92)
			return (0);
	}
	return (1);
}
