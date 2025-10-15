/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:00:00 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/15 02:44:22 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	init_player(t_game *game)
{
	game->player.radius = 5;
	game->player.turn_direction = 0;
	game->player.strafe_direction = 0;
	game->player.walk_direction = 0;
	game->player.move_speed = 5.0;
	game->player.rotation_speed = 3 * (M_PI / 180);
}

bool	is_valid_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->disp.num_doors)
	{
		if (game->disp.doors[i].x == x && game->disp.doors[i].y == y)
		{
			if (game->disp.doors[i].is_open)
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.map_width || y < 0
		|| y >= game->map.map_height)
		return (false);
	if (game->map.grid[y][x] == '1')
		return (false);
	if (game->map.grid[y][x] == 'D' && is_valid_door(game, x, y))
		return (false);
	return (true);
}

void	update_player_strafe(t_game *game)
{
	float	strafe_step;
	float	buffer;
	t_coord	new_pos;

	strafe_step = game->player.strafe_direction * game->player.move_speed
		/ TILE_SIZE;
	new_pos.x = game->player.pos.x + cos(game->player.rotation_angle + M_PI_2)
		* strafe_step;
	new_pos.y = game->player.pos.y + sin(game->player.rotation_angle + M_PI_2)
		* strafe_step;
	buffer = 0.05;
	if (is_valid_position(game, new_pos.x + buffer, game->player.pos.y)
		&& is_valid_position(game, new_pos.x - buffer, game->player.pos.y))
		game->player.pos.x = new_pos.x;
	if (is_valid_position(game, game->player.pos.x, new_pos.y + buffer)
		&& is_valid_position(game, game->player.pos.x, new_pos.y - buffer))
		game->player.pos.y = new_pos.y;
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
