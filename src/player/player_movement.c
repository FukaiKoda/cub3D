/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:00:00 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/10 11:33:17 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	init_player(t_game *game)
{
	game->player.radius = 5;
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.move_speed = 3.0;
	game->player.rotation_speed = 3 * (M_PI / 180);
}

bool	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.map_width || y < 0
		|| y >= game->map.map_height)
		return (false);
	if (game->map.greed[y][x] == '1')
		return (false);
	return (true);
}

void	update_player(t_game *game)
{
	float	move_step;
	float	buffer;
	t_coord	new_pos;

	move_step = game->player.walk_direction * game->player.move_speed
		/ TILE_SIZE;
	game->player.rotation_angle += game->player.turn_direction
		* game->player.rotation_speed;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	new_pos.x = game->player.pos.x + cos(game->player.rotation_angle)
		* move_step;
	new_pos.y = game->player.pos.y + sin(game->player.rotation_angle)
		* move_step;
	buffer = 0.05;
	if (is_valid_position(game, new_pos.x + buffer, game->player.pos.y)
		&& is_valid_position(game, new_pos.x - buffer, game->player.pos.y))
		game->player.pos.x = new_pos.x;
	if (is_valid_position(game, game->player.pos.x, new_pos.y + buffer)
		&& is_valid_position(game, game->player.pos.x, new_pos.y - buffer))
		game->player.pos.y = new_pos.y;
}
