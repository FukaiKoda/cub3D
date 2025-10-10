/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:13:18 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/08 17:47:41 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	init_rendering(t_game *game)
{
	game->disp.mlx = mlx_init();
	if (!game->disp.mlx)
		exit_game(0);
	game->disp.window = mlx_new_window(game->disp.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->disp.window)
		exit_game(0);
	game->disp.img = mlx_new_image(game->disp.mlx, WIDTH, HEIGHT);
	if (!game->disp.img)
		exit_game(0);
	game->disp.pixel = mlx_get_data_addr(game->disp.img, &game->disp.bpp,
			&game->disp.line_len, &game->disp.endian);
}
