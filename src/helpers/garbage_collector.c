/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:28:32 by habdella          #+#    #+#             */
/*   Updated: 2025/09/16 22:07:08 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

t_game	*save_game(t_game *game)
{
	static t_game	*saved;

	if (game)
		saved = game;
	return (saved);
}

void	burn_garbage()
{
	t_gc	*curr;
	t_gc	*nxt;
	t_game	*game;

	game = save_game(0);
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

void	add_to_garbage(void *ptr)
{
	t_gc	*node;
	t_gc	*curr;
	t_game	*game;

	game = save_game(0);
	node = malloc(sizeof(t_gc));
	if (!node)
		return (burn_garbage());
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

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		burn_garbage();
		exit(1);
	}
	add_to_garbage(p);
	return (p);
}

void	clean_exit(char *message)
{
	t_game	*game;

	game = save_game(0);
	if (message)
		putstr_fd(message, 2);
	if (game->file.fd)
		close(game->file.fd);
	burn_garbage();
	if (message)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
