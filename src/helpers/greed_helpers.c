/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greed_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:16:07 by habdella          #+#    #+#             */
/*   Updated: 2025/09/29 22:58:42 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	save_cord_player(t_game *game, int i, int j, char direction)
{
	if (game->player.is_exist)
		clean_exit("duplicated player");
	game->player.pos.x = j + 0.5;
	game->player.pos.y = i + 0.5;
	if (direction == 'N')
		game->player.rotation_angle = 3 * M_PI / 2;
	else if (direction == 'S')
		game->player.rotation_angle = M_PI / 2;
	else if (direction == 'E')
		game->player.rotation_angle = 0;
	else
		game->player.rotation_angle = M_PI;
	game->player.is_exist = true;
	game->map.greed[i][j] = '0';
}
