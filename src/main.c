/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:06:59 by habdella          #+#    #+#             */
/*   Updated: 2025/10/14 23:03:59 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dcast.h"

inline static int	game_loop(t_game *game)
{
	t_coord	pos;
	t_coord	size;

	update_animation(game);
	pos = (t_coord){0, 0};
	size = (t_coord){WIDTH, game->half_height};
	rectangle(game, pos, size, game->disp.ceiling);
	pos = (t_coord){0, game->half_height};
	rectangle(game, pos, size, game->disp.floor);
	render_3d(game);
	if (game->display_minimap)
		display_minimap(game);
	mlx_put_image_to_window(game->disp.mlx, game->disp.window,
		game->disp.img, 0, 0);
	fps_counter(game);
	display_fps(game);
	return (0);
}

inline static void	start_game(t_game *game)
{
	game->mouse_pause = true;
	game->half_fov = FOV_ANGLE / 2.0;
	game->half_width = WIDTH / 2.0;
	game->half_height = HEIGHT / 2.0;
	game->proj_plane_dist = game->half_width / tan(game->half_fov);
	init_rendering(game);
	init_textures(game);
	init_events(game);
	init_player(game);
	init_rays(game);
	mlx_loop_hook(game->disp.mlx, game_loop, game);
	mlx_loop(game->disp.mlx);
	clean_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (initial_checks(argc, argv))
		return (1);
	memset(&game, 0, sizeof(t_game));
	save_game(&game);
	parse_map(&game, argv[1]);
	start_game(&game);
	return (0);
}
