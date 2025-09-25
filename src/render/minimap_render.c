/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:28:22 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 09:06:02 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

static void  draw_player(t_game *game)
{
    int px = game->player.x;
    int py = game->player.y;
    int size = 6;
    int i = 0;
    int j;

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_pixel_put(px + i, py + j, game, BLACK);
            j++;
        }
        i++;
    }
}

static void  fill_tils(t_game *game, int ty, int tx, int color)
{
    int y;
    int x;

    y = 0;
    while (y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            my_pixel_put(tx * TILE_SIZE + x, ty * TILE_SIZE + y, game, color);
            x++;
        }
        y++;
    }
}

static int  which_color(t_game *game, int ty, int tx)
{
    if (game->map.greed[ty][tx] == '1')
        return (DARK_GRAY);
    else if (game->map.greed[ty][tx] == '0')
        return (WHITE);
    else if (game->map.greed[ty][tx] == ' ')
        return (GRAY);
    return (WHITE);
}

void    minimap_render(t_game *game)
{
    int ty;
    int tx;
    int color;

    ty = 0;
    tx = 0;
    while (ty < game->map.map_height)
    {
        tx = 0;
        while (tx < game->map.map_width)
        {
            color = which_color(game, ty, tx);
            fill_tils(game, ty, tx, color);
            tx++;
        }
        ty++;
    }
    draw_player(game);
    mlx_put_image_to_window(game->disp.mlx, game->disp.window \
        , game->disp.img, 0, 0);
}
