/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:00:00 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/10 11:44:02 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	my_pixel_put(int x, int y, t_game *game, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * game->disp.line_len) + (x * (game->disp.bpp / 8));
	*(unsigned int *)(game->disp.pixel + offset) = color;
}

void	rectangle(t_game *game, t_coord pos, t_coord size, int color)
{
	int	i;
	int	j;
	int	width;
	int	height;

	width = (int)size.x;
	height = (int)size.y;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			my_pixel_put((int)pos.x + j, (int)pos.y + i, game, color);
			j++;
		}
		i++;
	}
}
