/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:22:35 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/11 23:28:21 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all_allocations(t_command *cmd)
{
	free(cmd->args);
	free(cmd->red_in);
	free(cmd->red_out);
	free(cmd->append);
	free(cmd->heredoc_delimiters);
	free(cmd->heredoc_quotes);
}
