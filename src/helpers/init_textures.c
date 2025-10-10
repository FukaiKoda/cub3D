/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:55:21 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/03 10:35:56 by oayyoub          ###   ########.fr       */
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
	path = game->disp.texture[index];
	if (!path)
		clean_exit("Texture path is NULL\n");
	tex->img = mlx_xpm_file_to_image(game->disp.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		putstr_fd("Error: Failed to load texture: ", 2);
		putstr_fd(path, 2);
		putstr_fd("\n", 2);
		clean_exit("Failed to load texture\n");
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->data)
		clean_exit("Failed to get texture data\n");
}

void	cleanup_textures(t_game *game)
{
	int	i;

	if (!game || !game->disp.mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->disp.tex[i].img)
		{
			mlx_destroy_image(game->disp.mlx, game->disp.tex[i].img);
			game->disp.tex[i].img = NULL;
		}
		i++;
	}
}

void	init_textures(t_game *game)
{
	int	i;

	if (!game->disp.mlx)
		clean_exit("MLX not initialized before loading textures\n");
	i = 0;
	while (i < 4)
	{
		load_single_texture(game, i);
		i++;
	}
}
