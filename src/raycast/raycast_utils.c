/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:00:00 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/15 23:38:57 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	init_rays(t_game *game)
{
	game->num_rays = WIDTH / WALL_STRIP_WIDTH;
	if (game->num_rays <= 0)
	{
		game->num_rays = 1;
	}
	game->angle_step = FOV_ANGLE / game->num_rays;
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	return (sqrt((delta_x * delta_x) + (delta_y * delta_y)));
}

int	is_inside_map(t_game *game, float x, float y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= game->map.map_width || y >= game->map.map_height)
		return (0);
	return (1);
}

bool	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	if (!is_inside_map(game, x, y))
		return (true);
	map_x = (int)x;
	map_y = (int)y;
	return (game->map.grid[map_y][map_x] == '1');
}
