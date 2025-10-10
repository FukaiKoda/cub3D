/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:44:40 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/09 10:54:16 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

inline static void	set_ray_direction(t_ray *ray)
{
	ray->is_ray_facing_down = (ray->ray_angle > 0 && ray->ray_angle < M_PI);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = (ray->ray_angle < 0.5 * M_PI
			|| ray->ray_angle > 1.5 * M_PI);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

inline static t_hit	select_hit(t_hit horizontal, t_hit vertical, t_ray *ray)
{
	if (vertical.found && (!horizontal.found
			|| vertical.distance < horizontal.distance))
	{
		if (ray->is_ray_facing_right)
			ray->wall_side = WE;
		else
			ray->wall_side = EA;
		ray->wall_x = fmod(vertical.pos.y, TILE_SIZE);
		return (vertical);
	}
	if (ray->is_ray_facing_down)
		ray->wall_side = NO;
	else
		ray->wall_side = SO;
	ray->wall_x = fmod(horizontal.pos.x, TILE_SIZE);
	return (horizontal);
}

inline static void	assign_hit(t_ray *ray, t_hit hit, t_coord player)
{
	if (!hit.found)
	{
		ray->wall_hit = player;
		ray->distance = 0;
		return ;
	}
	ray->wall_hit = hit.pos;
	ray->distance = hit.distance;
}

t_ray	cast_single_ray(t_game *game, float angle, t_coord player)
{
	t_ray	ray;
	t_hit	horizontal;
	t_hit	vertical;
	t_hit	final;

	ray.ray_angle = normalize_angle(angle);
	set_ray_direction(&ray);
	horizontal = find_horizontal(game, &ray, player);
	vertical = find_vertical(game, &ray, player);
	final = select_hit(horizontal, vertical, &ray);
	assign_hit(&ray, final, player);
	return (ray);
}
