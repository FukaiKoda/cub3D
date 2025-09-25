/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:06:59 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 14:09:49 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dcast.h"

void    init_player(t_player *player)
{
    player->radius = 3;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->moveSpeed = 3.0;
    player->rotationAngle = PI / 2;
    player->rotaionSpeed = 3 * (PI / 180);
}

int main(int argc, char **argv)
{
    t_game game;

    if (initial_checks(argc, argv))
        return 1;
    save_game(&game);
    memset(&game, 0, sizeof(game));
    parse_map(&game, argv[1]);
    init_render(&game);
    init_player(&game.player);
    // mainmap_render(game);
    minimap_render(&game);
    mlx_loop(game.disp.mlx);
    clean_exit(NULL);
    return 0;
}
