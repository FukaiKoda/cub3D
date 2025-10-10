/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:22:56 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/09 11:49:16 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

inline static void	prepare_wall(t_game *game, t_ray *ray, t_wall *wall)
{
	float	distance;
	float	top;
	float	bottom;
	float	angle;

	angle = ray->ray_angle - game->player.rotation_angle;
	distance = ray->distance * cos(angle);
	wall->height = (TILE_SIZE / distance) * game->proj_plane_dist;
	top = game->half_height - (wall->height / 2.0f);
	bottom = game->half_height + (wall->height / 2.0f);
	if (top < 0)
		top = 0;
	if (bottom > HEIGHT)
		bottom = HEIGHT;
	wall->top = top;
	wall->bottom = bottom;
	wall->start = (int)top;
	wall->end = (int)bottom;
}

inline static void	draw_column(t_game *game, t_wall *wall, t_texture *texture)
{
	t_tex	tex;

	tex.step = texture->height / wall->height;
	tex.base = game->half_height - (wall->height / 2.0f);
	tex.pos = (wall->start - tex.base) * tex.step;
	tex.y = wall->start;
	while (tex.y < wall->end)
	{
		tex.tex_y = (int)tex.pos;
		if (tex.tex_y < 0)
			tex.tex_y = 0;
		else if (tex.tex_y >= texture->height)
			tex.tex_y = texture->height - 1;
		tex.color = get_texture_color(texture, wall->tex_x, tex.tex_y);
		tex.column = 0;
		while (tex.column < WALL_STRIP_WIDTH)
		{
			if (wall->screen_x + tex.column >= WIDTH)
				break ;
			my_pixel_put(wall->screen_x + tex.column, tex.y, game, tex.color);
			tex.column++;
		}
		tex.pos += tex.step;
		tex.y++;
	}
}

inline static void	render_wall_strip(t_game *game, t_ray *ray, int id)
{
	t_wall		wall;
	t_texture	*texture;

	prepare_wall(game, ray, &wall);
	wall.screen_x = id * WALL_STRIP_WIDTH;
	texture = &game->disp.tex[ray->wall_side];
	wall.tex_x = (int)((ray->wall_x / (float)TILE_SIZE) * texture->width);
	if (wall.tex_x < 0)
		wall.tex_x = 0;
	else if (wall.tex_x >= texture->width)
		wall.tex_x = texture->width - 1;
	draw_column(game, &wall, texture);
}

void	render_3d(t_game *game)
{
	int		col;
	float	ray_angle;
	t_coord	player_pos;
	t_ray	ray;

	if (game->num_rays <= 0)
		return ;
	ray_angle = game->player.rotation_angle - game->half_fov;
	player_pos.x = game->player.pos.x * TILE_SIZE;
	player_pos.y = game->player.pos.y * TILE_SIZE;
	col = 0;
	while (col < game->num_rays)
	{
		ray = cast_single_ray(game, ray_angle, player_pos);
		render_wall_strip(game, &ray, col);
		ray_angle += game->angle_step;
		col++;
	}
}
