/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:30:12 by habdella          #+#    #+#             */
/*   Updated: 2025/10/08 17:47:59 by oayyoub          ###   ########.fr       */
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
	if (keycode == 119)
		game->player.walk_direction = 1;
	else if (keycode == 115)
		game->player.walk_direction = -1;
	else if (keycode == 97)
		game->player.turn_direction = -1;
	else if (keycode == 100)
		game->player.turn_direction = 1;
	else if (keycode == 65307)
		exit_game(0);
	else if (keycode == 65289)
		game->display_minimap = !game->display_minimap;
	else
		return (0);
	update_player(game);
	return (0);
}

static int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 115)
		game->player.walk_direction = 0;
	else if (keycode == 97 || keycode == 100)
		game->player.turn_direction = 0;
	return (0);
}

void	init_events(t_game *game)
{
	mlx_hook(game->disp.window, 17, 1, exit_game, 0);
	mlx_hook(game->disp.window, 2, 1, handle_keypress, game);
	mlx_hook(game->disp.window, 3, 2, handle_keyrelease, game);
}
