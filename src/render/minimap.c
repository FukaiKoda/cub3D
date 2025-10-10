/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 21:24:39 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/09 11:41:36 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

inline static void	line(t_game *game, t_coord start, t_coord end, int color)
{
	t_coord	delta;
	float	steps;
	t_coord	increment;
	t_coord	current;
	int		i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	steps = fmax(fabs(delta.x), fabs(delta.y));
	increment.x = delta.x / steps;
	increment.y = delta.y / steps;
	current.x = start.x;
	current.y = start.y;
	i = 0;
	while (i <= steps)
	{
		my_pixel_put(current.x, current.y, game, color);
		current.x += increment.x;
		current.y += increment.y;
		i++;
	}
}

inline static void	circle(int center_x, int center_y, int radius, t_game *game)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				dx = center_x + x;
				dy = center_y + y;
				my_pixel_put(dx, dy, game, RED);
			}
			x++;
		}
		y++;
	}
}

inline static void	draw_minimap_tiles(t_game *game, int minimap_size)
{
	int		i;
	int		j;
	int		color;
	t_coord	pos;
	t_coord	size;

	i = 0;
	while (i < game->map.map_height)
	{
		j = 0;
		while (j < game->map.map_width)
		{
			if (game->map.greed[i][j] == '1')
				color = BLACK;
			else
				color = WHITE;
			pos = (t_coord){j * minimap_size, i * minimap_size};
			size = (t_coord){minimap_size, minimap_size};
			rectangle(game, pos, size, color);
			j++;
		}
		i++;
	}
}

void	display_minimap(t_game *game)
{
	int	minimap_size;

	minimap_size = 16;
	draw_minimap_tiles(game, minimap_size);
	circle(game->player.pos.x * minimap_size, game->player.pos.y * minimap_size,
		3, game);
	line(game, (t_coord){game->player.pos.x * minimap_size,
		game->player.pos.y * minimap_size},
		(t_coord){(game->player.pos.x + cos(game->player.rotation_angle) * 1)
		* minimap_size, (game->player.pos.y + sin(game->player.rotation_angle)
			* 1) * minimap_size}, RED);
}
