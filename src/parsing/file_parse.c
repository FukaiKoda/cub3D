/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 08:49:31 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 08:19:06 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

bool	is_valid_element(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\x7f'
		|| c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == 'V');
}

bool is_empty_line(char *s)
{
	if (!s)
		return true;
	while (*s)
	{
		if (*s != 32)
			return (false);
		s++;
	}
	return (true);
}

int	which_type(char **split, int size)
{
	if (size != 2)
		return (-1);
	if (!ft_strcmp(*split, "NO"))
		return (NO);
	if (!ft_strcmp(*split, "EA"))
		return (EA);
	if (!ft_strcmp(*split, "SO"))
		return (SO);
	if (!ft_strcmp(*split, "WE"))
		return (WE);
	if (!ft_strcmp(*split, "F"))
		return (FLOOR);
	if (!ft_strcmp(*split, "C"))
		return (CEILING);
	return (-1);
}

void	scan_map_inputs(t_game *game)
{
    char    *line;
	int		i;
	int		type;
	int		size;
	char	mask;

	(1) && (i = 0, mask = 0);
	while (i < 6)
	{
		line = get_next_line(game, game->file.fd);
		if (!line)
			break ;
		if (is_empty_line(line))
			continue;
		game->split = ft_split(line, WHITESPACES, &size);
		type = which_type(game->split, size);
		if (type == -1)
			clean_exit("Invalid format\n");
		else if (type <= 3)
			textures_parse(game, &mask, type);
		else
			floor_ceiling_parse(game, &mask, type);
		i++;
	}
	greed_parse(game);
}

void	parse_map(t_game *game, char *argv)
{
	game->file.name = argv;
    game->file.fd = open(game->file.name, O_RDONLY);
    scan_map_inputs(game);
    close(game->file.fd);
    return ;
}