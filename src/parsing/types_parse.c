/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:33:55 by habdella          #+#    #+#             */
/*   Updated: 2025/10/08 11:15:37 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	grid_parse(t_game *game)
{
	char	*line;
	int		len;

	game->map.map_width = INT_MIN;
	line = get_next_line(game, game->file.fd);
	while (line && is_empty_line(line))
		line = get_next_line(game, game->file.fd);
	if (!line)
		clean_exit("No Map found\n");
	while (line)
	{
		len = ft_strlen(line);
		if (game->map.map_width < len)
			game->map.map_width = len;
		if (len == 0)
			clean_exit("Empty line in the map\n");
		add_back(&game->list, line);
		game->map.map_height++;
		line = get_next_line(game, game->file.fd);
	}
	convert_list_to_array(game);
	check_valid_grid(game);
	return ;
}

void	floor_ceiling_parse(t_game *game, char *mask, int type)
{
	int		r;
	int		g;
	int		b;

	game->split = ft_split(game->split[1], ",", &game->split_len);
	if (game->split_len != 3)
		clean_exit("Invalid number of RGB colors\n");
	if ((*mask & (1 << type)))
		clean_exit("duplicated type\n");
	*mask |= (1 << type);
	if (type == FLOOR)
	{
		r = ft_atoi(game->split[0]);
		g = ft_atoi(game->split[1]);
		b = ft_atoi(game->split[2]);
		game->disp.floor = r << 16 | g << 8 | b;
		return ;
	}
	r = ft_atoi(game->split[0]);
	g = ft_atoi(game->split[1]);
	b = ft_atoi(game->split[2]);
	game->disp.ceiling = r << 16 | g << 8 | b;
}

void	textures_parse(t_game *game, char *mask, int type)
{
	game->disp.texture[type] = game->split[1];
	if (*mask & (1 << type))
		clean_exit("duplicated type\n");
	*mask |= (1 << type);
}
