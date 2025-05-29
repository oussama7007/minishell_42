/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:42 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/28 15:28:43 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_functions.h"

typedef struct s_gc_list
{
	void				*ptr;
	struct s_gc_list	*next;
} t_gc_list;

typedef struct s_head_list
{
	t_gc_list	*head;
}				t_head_list;

void	gc_init(t_head_list *head);
void	*gc_malloc(t_head_list *head, size_t size);
void	gc_free_all(t_head_list *head);
char	*gc_strdup(t_head_list *head, const char *s);

void	gc_init(t_head_list *head) {
	if (head)
		head->head = NULL;
}
void gc_free_all(t_head_list *head) {
	if (!head)
		return ;
	t_gc_list *curr = head->head;
	while (curr) {
		t_gc_list *next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	head->head = NULL;
}

char	*gc_strdup(t_head_list *head, const char *s) {
	if (!s)
		return (NULL);
	size_t len = strlen(s) + 1;
	char *dup = gc_malloc(head, len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}




void	*gc_malloc(t_head_list *head, size_t size)
{
	if (!head)
		return (NULL);
	void	*ptr = malloc(size);
	if (!ptr) {
		gc_free_all(head);
		write(2, "gc_malloc: failed to allocate for a ptr\n",ft_strlen("gc_malloc: failed to allocate for a ptr\n"));
		exit(EXIT_FAILURE);// 1
	}
	t_gc_list *node = malloc(sizeof(t_gc_list));
	if (!node)
	{
		free(ptr);
		gc_free_all(head);
		write(2,"gc_malloc: failed to allocate node\n",ft_strlen("gc_malloc: failed to allocate node\n"));
		exit(EXIT_FAILURE);// 1
	}
	node->ptr = ptr;
	node->next = head->head;
	head->head = node;
	return (ptr);
}
