/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:33:55 by habdella          #+#    #+#             */
/*   Updated: 2025/09/16 16:12:25 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

void	greed_parse(t_game *game)
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
		add_back(&game->list, line);
		game->map.map_height++;
		line = get_next_line(game, game->file.fd);
	}
	convert_list_to_array(game);
	check_valid_greed(game);
	return ;
}

void	floor_ceiling_parse(t_game *game, char *mask, int type)
{
	game->split = ft_split(game->split[1], ",", &game->split_len);
	if (game->split_len != 3)
		clean_exit("Invalid number of RGB colors\n");
	if ((*mask & (1 << type)))
		clean_exit("duplicated type\n");
	*mask |= (1 << type);
	if (type == FLOOR)
	{
		game->disp.floor.red = ft_atoi(game->split[0]);
		game->disp.floor.green = ft_atoi(game->split[1]);
		game->disp.floor.blue = ft_atoi(game->split[2]);
		return ;
	}
	game->disp.ceiling.red = ft_atoi(game->split[0]);
	game->disp.ceiling.green = ft_atoi(game->split[1]);
	game->disp.ceiling.blue = ft_atoi(game->split[2]);
}

void	textures_parse(t_game *game, char *mask, int type)
{
	game->disp.texture[type] = game->split[1];
	if (*mask & (1 << type))
		clean_exit("duplicated type\n");
	*mask |= (1 << type);
}
