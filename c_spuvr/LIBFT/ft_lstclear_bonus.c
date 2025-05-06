/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:14:46 by oadouz            #+#    #+#             */
/*   Updated: 2024/11/17 04:12:26 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*n;
	t_list	*temp;

	if (!lst || !del)
		return ;
	n = *lst;
	while (n != NULL)
	{
		temp = n;
		n = n->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
