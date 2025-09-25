/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:22:09 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 09:20:40 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

void	my_pixel_put(int x, int y, t_game *game, int color)
{
	int	offset;

	offset = (y * game->disp.line_len) + (x * (game->disp.bpp / 8));
	*(unsigned int *)(game->disp.pixel + offset) = color;
}

void    init_render(t_game *game)
{
    game->disp.mlx = mlx_init();
    if (!game->disp.mlx)
        clean_exit("");
    game->disp.window = mlx_new_window(game->disp.mlx, WIDTH, HEIGHT, "");
    if (!game->disp.window)
    {
        mlx_destroy_window(game->disp.mlx, game->disp.window);
        mlx_destroy_display(game->disp.mlx);
        free(game->disp.mlx);
        clean_exit("");
    }
    game->disp.img = mlx_new_image(game->disp.mlx, WIDTH, HEIGHT);
    if (!game->disp.img)
    {
        mlx_destroy_image(game->disp.mlx, game->disp.img);
        mlx_destroy_window(game->disp.mlx, game->disp.window);
        mlx_destroy_display(game->disp.mlx);
        free(game->disp.mlx);
        clean_exit("");
    }
    game->disp.pixel = mlx_get_data_addr(game->disp.img, &game->disp.bpp \
        , &game->disp.line_len, &game->disp.endian);
    init_events(game);
}
