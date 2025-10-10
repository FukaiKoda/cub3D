/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:06:27 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/08 10:51:48 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	fps_counter(t_game *game)
{
	static int		frame_count = 0;
	static time_t	start_time = 0;
	time_t			current_time;
	float			elapsed_time;

	frame_count++;
	current_time = time(NULL);
	if (start_time == 0)
		start_time = current_time;
	elapsed_time = difftime(current_time, start_time);
	if (elapsed_time >= 1.0)
	{
		game->fps = frame_count / elapsed_time;
		frame_count = 0;
		start_time = current_time;
	}
}

void	display_fps(t_game *game)
{
	char	fps_str[20];

	snprintf(fps_str, sizeof(fps_str), "FPS: %d", game->fps);
	mlx_string_put(game->disp.mlx, game->disp.window, 10, 10, GREEN, fps_str);
}
