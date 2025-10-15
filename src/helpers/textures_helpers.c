/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:08:55 by habdella          #+#    #+#             */
/*   Updated: 2025/10/15 23:01:57 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	init_animated_textures(t_game *game, char *paths[])
{
	game->disp.tex_anim.num_frames = 6;
	game->disp.tex_anim.current_frame = 0;
	game->disp.tex_anim.frame_time = 0.1f;
	game->disp.tex_anim.elapsed_time = 0;
	paths[0] = "./assets/wall_torch_01.xpm";
	paths[1] = "./assets/wall_torch_02.xpm";
	paths[2] = "./assets/wall_torch_03.xpm";
	paths[3] = "./assets/wall_torch_04.xpm";
	paths[4] = "./assets/wall_torch_05.xpm";
	paths[5] = "./assets/wall_torch_06.xpm";
}

void	load_animated_texture(t_game *game, int index, char *path)
{
	t_texture	*frame;

	frame = &game->disp.tex_anim.frames[index];
	frame->img = mlx_xpm_file_to_image(game->disp.mlx, path,
			&frame->width, &frame->height);
	if (!frame->img)
	{
		putstr_fd("Error: Failed to load texture: ", 2);
		putstr_fd(path, 2);
		putstr_fd("\n", 2);
		clean_exit(0);
	}
	frame->data = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_len, &frame->endian);
	if (!frame->data)
	{
		putstr_fd("Failed to get texture data\n", 2);
		clean_exit(0);
	}
}

void	clean_animated_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->disp.tex_anim.frames[i].img)
		{
			mlx_destroy_image(game->disp.mlx,
				game->disp.tex_anim.frames[i].img);
			game->disp.tex_anim.frames[i].img = NULL;
		}
		i++;
	}
}

void	load_door_texture(t_game *game)
{
	t_texture	*tex;

	tex = &game->disp.tex[4];
	tex->is_animated = false;
	tex->img = mlx_xpm_file_to_image(game->disp.mlx, "./assets/door.xpm",
			&tex->width, &tex->height);
	if (!tex->img)
	{
		putstr_fd("Error: Failed to load texture: ", 2);
		putstr_fd("./assets/door.xpm", 2);
		putstr_fd("\n", 2);
		exit_game(0);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->data)
	{
		putstr_fd("Failed to get texture data\n", 2);
		exit_game(0);
	}
}

bool	is_closed_door(t_game *game, bool *horz_vert, float x, float y)
{
	int	i;
	int	map_x;
	int	map_y;

	i = 0;
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	while (i < game->disp.num_doors)
	{
		if (game->disp.doors[i].is_open == false)
		{
			if (game->disp.doors[i].x == map_x
				&& game->disp.doors[i].y == map_y)
			{
				*horz_vert = true;
				return (true);
			}
		}
		i++;
	}
	return (false);
}
