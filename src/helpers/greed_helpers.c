/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greed_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:16:07 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 09:10:08 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	save_cord_player(t_game *game, int x, int y, char direction)
{
	if (game->player.x != -1)
		clean_exit("duplicated player");
	game->player.x = (y * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.y = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.dir = direction;
}
