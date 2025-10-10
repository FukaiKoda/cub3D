/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:06:13 by habdella          #+#    #+#             */
/*   Updated: 2025/09/30 09:25:59 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

t_list	*new_node(char *content)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	node->line = content;
	node->next = NULL;
	return (node);
}

void	add_back(t_list **head, char *content)
{
	t_list	*new;
	t_list	*last;

	if (!head)
		return ;
	new = new_node(content);
	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}
