/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greed_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:47:03 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 09:09:56 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

void	floodfill(t_game *game, char **greed, int x, int y)
{
	if (x < 0 || x >= game->map.map_height || y < 0 || y >= game->map.map_width)
		clean_exit("Invalid map\n");
	
	if (greed[x][y] == '\x7f' || greed[x][y] == '1')
		return ;

	if (!is_valid_element(greed[x][y]))
		clean_exit("Invalid map character\n");

	if (is_player(greed[x][y]))
		save_cord_player(game, x, y, greed[x][y]);

	greed[x][y] = '\x7f'; // it will be modified

	floodfill(game, greed, x + 1, y);
	floodfill(game, greed, x - 1, y);
	floodfill(game, greed, x, y + 1);
	floodfill(game, greed, x, y - 1);
}

char	**map_copy(t_game *game)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_malloc(sizeof(char *) * (game->map.map_height + 1));
	copy[game->map.map_height] = NULL;
	while (i < game->map.map_height)
	{
		copy[i] = ft_strdup(game->map.greed[i]);
		i++;
	}
	return (copy);
}

void	check_valid_greed(t_game *game)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	copy = map_copy(game);
	game->player.x = -1;
	game->player.y = -1;
	while (i < game->map.map_height)
	{
		j = 0;
		while (j < game->map.map_width)
		{
			if (copy[i][j] == '0' || is_player(copy[i][j]))
				floodfill(game, copy, i, j);
			else if (!is_valid_element(copy[i][j]))
				clean_exit("Invalid map character\n");
			j++;
		}
		i++;
	}
}

char *ft_strdup_pad(const char *src, int width)
{
	char *dest;
	int i;

	dest = ft_malloc(width + 1);
	i = 0;
	while (i < width && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < width)
		dest[i++] = ' ';
	dest[i] = '\0';
	return dest;
}

void	convert_list_to_array(t_game *game)
{
	int		index;
	t_list	*curr;

	index = 0;
	game->map.greed = ft_malloc(sizeof(char *) * (game->map.map_height + 1));
	game->map.greed[game->map.map_height] = NULL;
	curr = game->list;
	while (curr)
	{
		game->map.greed[index++] = ft_strdup_pad(curr->line, game->map.map_width);
		curr = curr->next;
	}
}
