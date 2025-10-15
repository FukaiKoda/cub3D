/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:16:07 by habdella          #+#    #+#             */
/*   Updated: 2025/09/29 22:58:42 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	count_doors(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'D')
			game->disp.num_doors++;
		i++;
	}
}

void	save_doors_coord(t_game *game)
{
	int		door_idx;
	int		i;
	int		j;

	i = 0;
	door_idx = 0;
	game->disp.doors = ft_malloc(sizeof(t_door) * game->disp.num_doors);
	while (i < game->map.map_height)
	{
		j = 0;
		while (j < game->map.map_width)
		{
			if (game->map.grid[i][j] == 'D')
			{
				game->disp.doors[door_idx].x = j;
				game->disp.doors[door_idx].y = i;
				game->disp.doors[door_idx].is_open = false;
				door_idx++;
			}
			j++;
		}
		i++;
	}
}

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
	game->map.grid[i][j] = '0';
}
