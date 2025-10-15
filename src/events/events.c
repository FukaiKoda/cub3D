/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:30:12 by habdella          #+#    #+#             */
/*   Updated: 2025/10/15 20:09:10 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

int	exit_game(void *arg)
{
	t_game	*game;

	(void)arg;
	game = save_game(NULL);
	cleanup_textures(game);
	mlx_destroy_image(game->disp.mlx, game->disp.img);
	mlx_destroy_window(game->disp.mlx, game->disp.window);
	mlx_destroy_display(game->disp.mlx);
	free(game->disp.mlx);
	clean_exit(0);
	return (0);
}

static int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		walk_turn_direction(keycode, game);
		return (0);
	}
	if (keycode == KEY_A || keycode == KEY_D)
	{
		strafe_direction(keycode, game);
		return (0);
	}
	if (keycode == KEY_R || keycode == KEY_H)
	{
		mouse_interaction(keycode, game);
		return (0);
	}
	if (keycode == KEY_O)
		return (door_interaction(game), 0);
	if (keycode == KEY_ESC)
		exit_game(0);
	if (keycode == KEY_TAB)
		game->display_minimap = !game->display_minimap;
	return (0);
}

static int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.walk_direction = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		game->player.strafe_direction = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player.turn_direction = 0;
	return (0);
}

int	handle_mouse(int x, int y, t_game *game)
{
	float	dx;

	(void)y;
	if (game->mouse_pause)
	{
		mlx_mouse_show(game->disp.mlx, game->disp.window);
		return (0);
	}
	dx = x - game->half_width;
	game->player.rotation_angle += dx * MOUSE_SENSITIVITY;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	mlx_mouse_move(game->disp.mlx, game->disp.window,
		game->half_width, game->half_height);
	return (0);
}

void	init_events(t_game *game)
{
	mlx_hook(game->disp.window, 17, 1, exit_game, 0);
	mlx_hook(game->disp.window, 2, 1, handle_keypress, game);
	mlx_hook(game->disp.window, 3, 2, handle_keyrelease, game);
	mlx_hook(game->disp.window, 6, 1L << 6, handle_mouse, game);
}
