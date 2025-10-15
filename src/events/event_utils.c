/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:57:38 by habdella          #+#    #+#             */
/*   Updated: 2025/10/15 20:59:49 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	walk_turn_direction(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.walk_direction = 1;
	else if (keycode == KEY_S)
		game->player.walk_direction = -1;
	else if (keycode == KEY_LEFT)
		game->player.turn_direction = -1;
	else if (keycode == KEY_RIGHT)
		game->player.turn_direction = 1;
	update_player(game);
}

void	strafe_direction(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->player.strafe_direction = -1;
	else if (keycode == KEY_D)
		game->player.strafe_direction = 1;
	update_player_strafe(game);
}

void	mouse_interaction(int keycode, t_game *game)
{
	if (keycode == KEY_R)
	{
		game->mouse_pause = true;
	}
	else if (keycode == KEY_H)
	{
		mlx_mouse_hide(game->disp.mlx, game->disp.window);
		game->mouse_pause = false;
	}
}

void	door_action(t_game *game, int save_x, int save_y, float min_dist)
{
	int	i;

	i = 0;
	while (i < game->disp.num_doors)
	{
		if (game->disp.doors[i].x == save_x && game->disp.doors[i].y == save_y)
		{
			if (min_dist < WALL_STRIP_WIDTH)
				game->disp.doors[i].is_open = !game->disp.doors[i].is_open;
			break ;
		}
		i++;
	}
}

void	door_interaction(t_game *game)
{
	int		i;
	int		save_x;
	int		save_y;
	float	min_dist;
	float	dist;

	i = 0;
	min_dist = INT_MAX;
	dist = min_dist;
	while (i < game->disp.num_doors)
	{
		dist = distance_between_points((float)game->disp.doors[i].x + 0.5,
				(float)game->disp.doors[i].y + 0.5, game->player.pos.x,
				game->player.pos.y);
		if (dist < min_dist)
		{
			min_dist = dist;
			save_x = game->disp.doors[i].x;
			save_y = game->disp.doors[i].y;
		}
		i++;
	}
	door_action(game, save_x, save_y, min_dist);
}
