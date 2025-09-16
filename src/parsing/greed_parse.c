/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greed_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:47:03 by habdella          #+#    #+#             */
/*   Updated: 2025/09/16 22:23:43 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/Dcast.h"

void	floodfill(t_game *game, bool **visited, int x, int y)
{
	if (x < 0 || x >= game->map.map_height || y < 0 || y >= game->map.map_width)
		clean_exit("Map is not closed\n");

	if (visited[x][y] || game->map.greed[x][y] == '1')
		return ;

	if (!is_valid_element(game->map.greed[x][y]))
		clean_exit("Invalid map character\n");

	if (is_player(game->map.greed[x][y]))
		save_cord_player(game, x, y, game->map.greed[x][y]);

	visited[x][y] = true;

	floodfill(game, visited, x + 1, y);
	floodfill(game, visited, x - 1, y);
	floodfill(game, visited, x, y + 1);
	floodfill(game, visited, x, y - 1);
}

bool	**init_visited(int height, int width)
{
	bool	**visited;
	int		i;
	int		j;

	i = 0;
	visited = ft_malloc(sizeof(bool *) * height);
	while (i < height)
	{
		visited[i] = ft_malloc(sizeof(bool) * width);
		j = 0;
		while (j < width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (visited);
}

void	check_valid_greed(t_game *game)
{
	char	**map;
	bool	**visited;
	int		i;
	int		j;

	i = 0;
	map = game->map.greed;
	visited = init_visited(game->map.map_height, game->map.map_width);
	game->player.x = -1;
	game->player.y = -1;
	while (i < game->map.map_height)
	{
		j = 0;
		while (j < game->map.map_width)
		{
			if (!visited[i][j] && (map[i][j] == '0' || is_player(map[i][j])))
				floodfill(game, visited, i, j);
			else if (!is_valid_element(map[i][j]))
				clean_exit("Invalid map character\n");
			j++;
		}
		i++;
	}
	if (game->player.x == -1)
		clean_exit("No player found\n");
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
