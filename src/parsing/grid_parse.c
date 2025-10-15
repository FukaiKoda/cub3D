/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:47:03 by habdella          #+#    #+#             */
/*   Updated: 2025/09/30 09:30:27 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

void	floodfill(t_game *game, bool **visited, int i, int j)
{
	if (i < 0 || i >= game->map.map_height || j < 0 || j >= game->map.map_width)
		clean_exit("Map is not closed\n");
	if (visited[i][j] || game->map.grid[i][j] == '1')
		return ;
	if (game->map.grid[i][j] == ' ')
		clean_exit("empty cell not surrounded by walls\n");
	if (!is_valid_element(game->map.grid[i][j]))
		clean_exit("Invalid map character\n");
	if (is_player(game->map.grid[i][j]))
		save_cord_player(game, i, j, game->map.grid[i][j]);
	visited[i][j] = true;
	floodfill(game, visited, i + 1, j);
	floodfill(game, visited, i - 1, j);
	floodfill(game, visited, i, j + 1);
	floodfill(game, visited, i, j - 1);
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

void	check_valid_grid(t_game *game)
{
	char	**map;
	bool	**visited;
	int		i;
	int		j;

	i = 0;
	map = game->map.grid;
	visited = init_visited(game->map.map_height, game->map.map_width);
	while (i < game->map.map_height)
	{
		j = 0;
		while (j < game->map.map_width)
		{
			if (!visited[i][j] && (map[i][j] == '0' || map[i][j] == 'D'
				|| is_player(map[i][j])))
				floodfill(game, visited, i, j);
			else if (!is_valid_element(map[i][j]))
				clean_exit("Invalid map character\n");
			j++;
		}
		i++;
	}
	if (!game->player.is_exist)
		clean_exit("No player found\n");
}

char	*ft_strdup_pad(const char *src, int width)
{
	char	*dest;
	int		i;

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
	return (dest);
}

void	convert_list_to_array(t_game *game)
{
	int		index;
	int		width;
	t_list	*curr;

	index = 0;
	game->disp.num_doors = 0;
	game->map.grid = ft_malloc(sizeof(char *) * (game->map.map_height + 1));
	game->map.grid[game->map.map_height] = NULL;
	curr = game->list;
	width = game->map.map_width;
	while (curr)
	{
		count_doors(game, curr->line);
		game->map.grid[index++] = ft_strdup_pad(curr->line, width);
		curr = curr->next;
	}
	save_doors_coord(game);
}
