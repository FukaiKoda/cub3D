/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:28:32 by habdella          #+#    #+#             */
/*   Updated: 2025/09/13 15:36:31 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dcast.h"

void	burn_garbage(t_game *game)
{
	t_gc	*curr;
	t_gc	*nxt;

	if (!game->collector)
		return ;
	curr = game->collector;
	while (curr)
	{
		nxt = curr->next;
		free(curr->address);
		free(curr);
		curr = nxt;
	}
	free(curr);
	game->collector = NULL;
}

void	add_to_garbage(t_game *game, void *ptr)
{
	t_gc	*node;
	t_gc	*curr;

	node = malloc(sizeof(t_gc));
	if (!node)
		return (burn_garbage(game));
	node->address = ptr;
	node->next = NULL;
	if (!game->collector)
	{
		game->collector = node;
		return ;
	}
	curr = game->collector;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
}

void	*ft_malloc(t_game *game, size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		burn_garbage(game);
		exit(1);
	}
	add_to_garbage(game, p);
	return (p);
}

void	clean_exit(t_game *game)
{
	burn_garbage(game);
	exit(1);
}