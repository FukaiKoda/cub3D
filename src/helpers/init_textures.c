/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:55:21 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/15 20:17:45 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

static void	load_single_texture(t_game *game, int index)
{
	t_texture	*tex;
	char		*path;

	tex = &game->disp.tex[index];
	tex->is_animated = false;
	path = game->disp.texture[index];
	if (!path)
		(1) && (putstr_fd("Texture path is NULL\n", 2), exit_game(0));
	if (!strncmp(path, "./assets/wall_torch_", 20))
		tex->is_animated = true;
	tex->img = mlx_xpm_file_to_image(game->disp.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		putstr_fd("Error: Failed to load texture: ", 2);
		(1) && (putstr_fd(path, 2), putstr_fd("\n", 2), exit_game(0));
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->data)
	{
		putstr_fd("Failed to get texture data\n", 2);
		exit_game(0);
	}
}

void	cleanup_textures(t_game *game)
{
	int	i;

	if (!game || !game->disp.mlx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (game->disp.tex[i].img)
		{
			mlx_destroy_image(game->disp.mlx, game->disp.tex[i].img);
			game->disp.tex[i].img = NULL;
		}
		i++;
	}
	clean_animated_textures(game);
}

void	init_textures(t_game *game)
{
	int		i;
	char	*paths[6];

	if (!game->disp.mlx)
		clean_exit("MLX not initialized before loading textures\n");
	i = 0;
	while (i < 4)
	{
		load_single_texture(game, i);
		i++;
	}
	if (game->disp.num_doors)
		load_door_texture(game);
	init_animated_textures(game, paths);
	i = 0;
	while (i < 6)
	{
		load_animated_texture(game, i, paths[i]);
		i++;
	}
}
