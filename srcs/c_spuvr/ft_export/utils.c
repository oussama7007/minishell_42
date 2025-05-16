/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:26:37 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/16 14:15:04 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built_functions.h"

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

char	*strip_outer_quotes(const char *str)
{
	size_t	len;
	int		has_quotes;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	has_quotes = 0;
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"') || 
			(str[0] == '\'' && str[len - 1] == '\''))
		{
			has_quotes = 1;
		}
	}
	if (has_quotes)
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

void	print_err_export(const char *context, const char *specific_arg)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (context && context[0] != '\0')
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd((char *)specific_arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
