/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:30:12 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 09:20:25 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

/* static int mouse_event(int x, int y, t_game *game)
{
    (void)x;
    (void)y;
    (void)game;
    return (0);
} */

static int close_event(t_game *game)
{
    mlx_destroy_image(game->disp.mlx, game->disp.img);
    mlx_destroy_window(game->disp.mlx, game->disp.window);
    mlx_destroy_display(game->disp.mlx);
    free(game->disp.mlx);
    clean_exit("");
    return (0);
}

static int keys_event(int keysym, t_game *game)
{
    if (keysym == KEY_ESC)
		close_event(game);
	else if (keysym == KEY_LEFT)
		game->player.x -= 10;
	else if (keysym == KEY_RIGHT)
		game->player.x += 10;
	else if (keysym == KEY_UP)
		game->player.y -= 10;
	else if (keysym == KEY_DOWN)
		game->player.y += 10;
    mlx_clear_window(game->disp.mlx, game->disp.window);
    minimap_render(game);
    return (0);
}

void    init_events(t_game *game)
{
    mlx_hook(game->disp.window, 17, 1L << 17, close_event, game);
    mlx_hook(game->disp.window, 2, 1L << 0, keys_event, game);
    // mlx_hook(game->disp.window, 6, 1L << 6, mouse_event, game);
}