/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:00:00 by oayyoub           #+#    #+#             */
/*   Updated: 2025/10/15 20:53:01 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

inline static void	setup_horizontal(t_ray *ray, t_step *step, t_coord player)
{
	float	tan_angle;

	tan_angle = tan(ray->ray_angle);
	step->pos.y = (int)(player.y / TILE_SIZE) *TILE_SIZE;
	if (ray->is_ray_facing_down)
		step->pos.y += TILE_SIZE;
	step->pos.x = player.x + (step->pos.y - player.y) / tan_angle;
	step->step.y = TILE_SIZE;
	if (ray->is_ray_facing_up)
		step->step.y *= -1;
	step->step.x = TILE_SIZE / tan_angle;
	if (ray->is_ray_facing_left && step->step.x > 0)
		step->step.x *= -1;
	if (ray->is_ray_facing_right && step->step.x < 0)
		step->step.x *= -1;
}

t_hit	find_horizontal(t_game *game, t_ray *ray, t_coord player)
{
	t_hit	hit;
	t_step	step;

	hit.found = false;
	hit.distance = INFINITY;
	hit.pos = (t_coord){0, 0};
	setup_horizontal(ray, &step, player);
	while (is_inside_map(game, step.pos.x, step.pos.y))
	{
		if (is_wall(game, step.pos.x, step.pos.y - ray->is_ray_facing_up)
			|| is_closed_door(game, &ray->horizontal_door, step.pos.x,
				step.pos.y - ray->is_ray_facing_up))
		{
			hit.found = true;
			hit.pos = step.pos;
			hit.distance = distance_between_points(player.x, player.y,
					hit.pos.x, hit.pos.y);
			break ;
		}
		step.pos.x += step.step.x;
		step.pos.y += step.step.y;
	}
	return (hit);
}
